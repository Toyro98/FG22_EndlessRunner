// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APlatformSpawner.generated.h"

UCLASS()
class FG22_ENDLESSRUNNER_API AAPlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPlatformSpawner();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Platform;

	UPROPERTY(EditAnywhere)
	uint8 AmountOfPlatformsToSpawn = 5;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnPlatforms(uint8 InAmount);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
