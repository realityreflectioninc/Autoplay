// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MotionControllerComponent.h"
#include "AutoplayVRRecord.generated.h"


/**
*
*/
USTRUCT()
struct AUTOPLAY_API FAutoplayVRRecord
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	float Time;

	UPROPERTY()
	ETrackingStatus TrackingStatus;

	UPROPERTY()
	FVector Position;

	UPROPERTY()
	FRotator Orientation;
};