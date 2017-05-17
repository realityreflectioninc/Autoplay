// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AutoplayManager.generated.h"

UCLASS()
class AUTOPLAY_API AAutoplayManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAutoplayManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Autoplay")
	static void Assert(bool Condition, const FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Autoplay")
	static void ShouldExecute(const FString& RoutineName);

	UFUNCTION(BlueprintCallable, Category = "Autoplay")
	static void Routine(const FString& Name);
	
};
