// Fill out your copyright notice in the Description page of Project Settings.

#include "Autoplay.h"
#include "AutoplayManager.h"
#include "AutoplayGameViewportClient.h"


// Sets default values
AAutoplayManager::AAutoplayManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAutoplayManager::BeginPlay()
{
	Super::BeginPlay();

	auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

	if (viewport == nullptr)
		return;

	viewport->InitLevel(UGameplayStatics::GetCurrentLevelName(GetWorld()));
}

// Called every frame
void AAutoplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAutoplayManager::Assert(bool Condition, const FString& Message)
{
	if (Condition)
		return;

	//Condition이 false인 경우 기록하기
	//실제 빌드에서는 날아가게? 흠.. 어떻게 하는게 좋을지
	//최소한 설정 정도는 할 수 있는게 좋을 듯 일단은 그냥 무조건 실행

	auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

	if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing)
		return;

	//이 경우 viewport에 assertion 결과 기록
	viewport->AddAssertionMessage(Message);
}

void AAutoplayManager::ShouldExecute(const FString& RoutineName)
{
	auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

	if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing)
		return;

	viewport->AddCheckList(RoutineName);
}

void AAutoplayManager::Routine(const FString& Name)
{
	auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

	if (viewport == nullptr || viewport->GetState() != EAutoplayState::Playing)
		return;

	viewport->Check(Name);
}

void AAutoplayManager::SetVRRecordEnable(bool Enable)
{
	auto viewport = Cast<UAutoplayGameViewportClient>(GEngine->GameViewport);

	if (viewport == nullptr)
		return;

	viewport->SetVRRecordEnable(Enable);
}