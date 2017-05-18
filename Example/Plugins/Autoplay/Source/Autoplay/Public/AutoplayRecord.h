// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "AutoplayInputRecord.h"
#include "AutoplayVRRecord.h"
#include "AutoplayRecord.generated.h"
/**
 * 
 */
USTRUCT()
struct AUTOPLAY_API FAutoplayRecord
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	TArray<FAutoplayInputRecord> Inputs;
	
	UPROPERTY()
	TArray<FAutoplayVRRecord> HMDInputs;
	
	UPROPERTY()
	TArray<FAutoplayVRRecord> LeftInputs;
	
	UPROPERTY()
	TArray<FAutoplayVRRecord> RightInputs;
};