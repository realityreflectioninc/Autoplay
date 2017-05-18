// Fill out your copyright notice in the Description page of Project Settings.

#include "Autoplay.h"
#include "AutoplayGameViewportClient.h"
#include "AutoplayManager.h"
#include "AutoplayConfig.h"
#include "JsonObjectConverter.h"

bool UAutoplayGameViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	if (State == EAutoplayState::Recording)
	{
		FAutoplayRecord record;
		
		record.Time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		record.Type = EAutoplayEventType::Key;
		record.ControllerId = ControllerId;
		record.Key = Key;
		record.EventType = EventType;
		record.AmountDepressed = AmountDepressed;
		record.bGamepad = bGamepad;

		Records.Add(record);
	}

	return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
}

bool UAutoplayGameViewportClient::InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if (State == EAutoplayState::Recording)
	{
		FAutoplayRecord record;

		record.Time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		record.Type = EAutoplayEventType::Axis;
		record.ControllerId = ControllerId;
		record.Key = Key;
		record.EventType = IE_Axis;
		record.Delta = Delta;
		record.DeltaTime = DeltaTime;
		record.NumSamples = NumSamples;
		record.bGamepad = bGamepad;

		Records.Add(record);
	}

	return Super::InputAxis(Viewport, ControllerId, Key, Delta, DeltaTime, NumSamples, bGamepad);
}

bool UAutoplayGameViewportClient::InputChar(FViewport* Viewport, int32 ControllerId, TCHAR Character)
{
	if (State == EAutoplayState::Recording)
	{
		FAutoplayRecord record;

		record.Time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		record.Type = EAutoplayEventType::Char;
		record.EventType = IE_MAX;
		record.Character.AppendChar(Character);

		Records.Add(record);
	}

	return Super::InputChar(Viewport, ControllerId, Character);
}

bool UAutoplayGameViewportClient::InputTouch(FViewport* Viewport, int32 ControllerId, uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	return Super::InputTouch(Viewport, ControllerId, Handle, Type, TouchLocation, DeviceTimestamp, TouchpadIndex);
}

bool UAutoplayGameViewportClient::InputMotion(FViewport* Viewport, int32 ControllerId, const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration)
{
	return Super::InputMotion(Viewport, ControllerId, Tilt, RotationRate, Gravity, Acceleration);
}

void UAutoplayGameViewportClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (State == EAutoplayState::Playing)
	{
		if (!bCompleteLoadRecords)
			return;

		//시간 되면 키 입력 재생해주기
		float time = UGameplayStatics::GetRealTimeSeconds(GetWorld());

		if (Records.Num() <= PlayIndex)
		{
			SaveResult();

			FString configPath;

			if (FParse::Value(FCommandLine::Get(), TEXT("autoplay"), configPath))
			{
				FString fileContents;

				FFileHelper::LoadFileToString(fileContents, *configPath);
				FAutoplayConfig config;

				FJsonObjectConverter::JsonObjectStringToUStruct(fileContents, &config, 0, 0);

				int nextIndex = -1;

				for (int i = 0; i < config.Autoplay.Num(); i++)
				{
					if (TestMapName == config.Autoplay[i])
					{
						nextIndex = i + 1;
						break;
					}
				}

				if (nextIndex == config.Autoplay.Num() || nextIndex == -1)
				{
					GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
				}
				else
				{
					GetWorld()->GetFirstPlayerController()->ConsoleCommand("open " + config.Autoplay[nextIndex]);
				}
			}
			else
			{
				GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
			}

			return;
		}

		while (PlayIndex < Records.Num() && Records[PlayIndex].Time < time)
		{
			switch (Records[PlayIndex].Type)
			{
			case EAutoplayEventType::Key:
				InputKey(Viewport, Records[PlayIndex].ControllerId, Records[PlayIndex].Key, Records[PlayIndex].EventType, Records[PlayIndex].AmountDepressed, Records[PlayIndex].bGamepad);
				break;
			case EAutoplayEventType::Axis:
				InputAxis(Viewport, Records[PlayIndex].ControllerId, Records[PlayIndex].Key, Records[PlayIndex].Delta, Records[PlayIndex].DeltaTime, Records[PlayIndex].NumSamples, Records[PlayIndex].bGamepad);
				break;
			case EAutoplayEventType::Char:
				InputChar(Viewport, Records[PlayIndex].ControllerId, Records[PlayIndex].Character[0]);
				break;
			}

			PlayIndex++;
		}
	}
}

void UAutoplayGameViewportClient::Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);

	TActorIterator<AAutoplayManager> iter(GetWorld());

	Records.Reset();
	Result = FAutoplayResult();

	if (FParse::Param(FCommandLine::Get(), TEXT("autoplay")))
	{
		State = EAutoplayState::Playing;
	}
	else if(iter)
	{
		State = EAutoplayState::Recording;
	}
	else
	{
		State = EAutoplayState::None;
	}
}

void UAutoplayGameViewportClient::BeginDestroy()
{
	if (State == EAutoplayState::Recording)
	{
		TArray<TSharedPtr<FJsonValue>> serializedData;
		for (auto& r : Records)
		{
			TSharedRef<FJsonValueObject> jsonValue = MakeShareable(new FJsonValueObject(FJsonObjectConverter::UStructToJsonObject(r)));
			serializedData.Add(jsonValue);
		}

		FString outputString;
		TSharedRef< TJsonWriter<> > writer = TJsonWriterFactory<>::Create(&outputString);

		if (FJsonSerializer::Serialize(serializedData, writer))
		{
			auto directory = FPaths::Combine(FPaths::GameDir(), "Tests");
			auto path = FPaths::Combine(directory, TestMapName + ".json");

			FFileHelper::SaveStringToFile(outputString, *path);
		}
	}

	Super::BeginDestroy();
}

void UAutoplayGameViewportClient::LoadRecords()
{
	//녹화한 거 재생하는 모드일 때만 동작하게
	if (State != EAutoplayState::Playing)
		return;

	FString str;
	auto directory = FPaths::Combine(FPaths::GameDir(), "Tests");
	auto path = FPaths::Combine(directory, TestMapName + ".json");
	FFileHelper::LoadFileToString(str, *path);

	FJsonObjectConverter::JsonArrayStringToUStruct(str, &Records, 0, 0);
	PlayIndex = 0;

	bCompleteLoadRecords = true;
}

void UAutoplayGameViewportClient::InitLevel(const FString& MapName)
{
	TestMapName = MapName;
	LoadRecords();
}

void UAutoplayGameViewportClient::SaveResult()
{
	auto directory = FPaths::Combine(FPaths::GameDir(), "Tests/Result");
	auto path = FPaths::Combine(directory, TestMapName + ".json");

	FFileHelper::SaveStringToFile(Result.ToJson(false), *path);
}