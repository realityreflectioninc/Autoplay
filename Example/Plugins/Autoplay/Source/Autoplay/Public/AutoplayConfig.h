#pragma once

#include "AutoplayConfig.generated.h"

USTRUCT()
struct AUTOPLAY_API FAutoplayConfig
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	bool UseEditor;

	UPROPERTY()
	FString EditorPath;
	
	UPROPERTY()
	FString Project;

	UPROPERTY()
	TArray<FString> Autoplay;
};