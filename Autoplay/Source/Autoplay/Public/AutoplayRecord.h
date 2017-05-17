// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "AutoplayRecord.generated.h"

UENUM()
enum class EAutoplayEventType : uint8
{
	Key,
	Axis,
	Char
};

/**
 * 
 */
USTRUCT()
struct AUTOPLAY_API FAutoplayRecord
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	EAutoplayEventType Type;

	UPROPERTY()
	float Time;

	UPROPERTY()
	int ControllerId = 0;

	UPROPERTY()
	FKey Key = EKeys::AnyKey;

	UPROPERTY()
	TEnumAsByte<EInputEvent> EventType = EInputEvent::IE_MAX;

	UPROPERTY()
	float AmountDepressed = 0.0f;

	UPROPERTY()
	bool bGamepad = false;

	UPROPERTY()
	float Delta = 0.0f;

	UPROPERTY()
	float DeltaTime = 0.0f;

	UPROPERTY()
	int NumSamples = 0;

	UPROPERTY()
	FString Character;
};