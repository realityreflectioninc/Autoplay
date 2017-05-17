// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Serialization/JsonSerializerMacros.h"

/**
 * 
 */
struct AUTOPLAY_API FAutoplayResult : public FJsonSerializable
{
public:
	TArray<FString> FailedAssertions;

	TMap<FString, int> RoutineCheckList;

	BEGIN_JSON_SERIALIZER
		JSON_SERIALIZE_ARRAY("FailedAssertions", FailedAssertions);
		JSON_SERIALIZE_MAP("RoutineCheckList", RoutineCheckList);
	END_JSON_SERIALIZER
};
