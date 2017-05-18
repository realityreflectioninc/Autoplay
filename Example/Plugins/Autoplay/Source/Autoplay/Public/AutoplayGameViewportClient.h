// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "AutoplayRecord.h"
#include "AutoplayResult.h"
#include "IMotionController.h"
#include "AutoplayGameViewportClient.generated.h"

UENUM()
enum class EAutoplayState : uint8
{
	None,
	Recording,
	Playing
};

/**
 * 
 */
UCLASS()
class AUTOPLAY_API UAutoplayGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
	virtual bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples = 1, bool bGamepad = false) override;
	virtual bool InputChar(FViewport* Viewport, int32 ControllerId, TCHAR Character) override;
	virtual bool InputTouch(FViewport* Viewport, int32 ControllerId, uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
	virtual bool InputMotion(FViewport* Viewport, int32 ControllerId, const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration) override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice = true) override;
	virtual void BeginDestroy() override;

	void LoadRecords();
	void AddAssertionMessage(const FString& Message)
	{
		Result.FailedAssertions.Add(Message);
	}

	EAutoplayState GetState() const { return State; }


	void AddCheckList(const FString& Check)
	{
		Result.RoutineCheckList.Add(Check, 0);
	}

	void Check(const FString& Message)
	{
		auto val = Result.RoutineCheckList.Find(Message);

		if (val != nullptr)
			*val = *val + 1;
	}

	void SetVRRecordEnable(bool enable) { bVRRecord = enable; }

	void InitLevel(const FString& MapName);

	void SaveResult();

	bool IsFinishPlaying() const;

	void RecordMotionController(EControllerHand Hand, ETrackingStatus TrackingStatus, const FVector& Position, const FRotator& Orientation);
	void RecordHMD(ETrackingStatus TrackingStatus, const FVector& Position, const FRotator& Orientation);

	FVector GetMotionControllerPosition(EControllerHand Hand) const
	{
		switch (Hand)
		{
		case EControllerHand::Left:
			if (Records.LeftInputs.Num() == 0)
				return FVector::ZeroVector;

			return Records.LeftInputs[FMath::Min(LeftPlayIndex, Records.LeftInputs.Num() - 1)].Position;
		case EControllerHand::Right:
			if (Records.RightInputs.Num() == 0)
				return FVector::ZeroVector;

			return Records.RightInputs[FMath::Min(LeftPlayIndex, Records.RightInputs.Num() - 1)].Position;
		}
		return FVector::ZeroVector;
	}

	FRotator GetMotionControllerOrientation(EControllerHand Hand)
	{
		switch (Hand)
		{
		case EControllerHand::Left:
			if (Records.LeftInputs.Num() == 0)
				return FRotator::ZeroRotator;

			return Records.LeftInputs[FMath::Min(LeftPlayIndex, Records.LeftInputs.Num() - 1)].Orientation;
		case EControllerHand::Right:
			if (Records.RightInputs.Num() == 0)
				return FRotator::ZeroRotator;

			return Records.RightInputs[FMath::Min(LeftPlayIndex, Records.RightInputs.Num() - 1)].Orientation;
		}
		return FRotator::ZeroRotator;
	}

	ETrackingStatus GetMotionControllerTrackingStatus(EControllerHand Hand)
	{
		switch (Hand)
		{
		case EControllerHand::Left:
			if (Records.LeftInputs.Num() == 0)
				return ETrackingStatus::NotTracked;

			return Records.LeftInputs[FMath::Min(LeftPlayIndex, Records.LeftInputs.Num() - 1)].TrackingStatus;
		case EControllerHand::Right:
			if (Records.RightInputs.Num() == 0)
				return ETrackingStatus::NotTracked;

			return Records.RightInputs[FMath::Min(LeftPlayIndex, Records.RightInputs.Num() - 1)].TrackingStatus;
		}
		return ETrackingStatus::NotTracked;
	}

private:
	int InputPlayIndex;
	int HMDPlayIndex;
	int LeftPlayIndex;
	int RightPlayIndex;

	FString TestMapName;
	EAutoplayState State;

	bool bCompleteLoadRecords = false;
	bool bVRRecord = false;

	FAutoplayRecord Records;
	FAutoplayResult Result;
};
