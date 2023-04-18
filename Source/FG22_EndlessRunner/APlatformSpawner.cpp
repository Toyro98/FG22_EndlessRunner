// Fill out your copyright notice in the Description page of Project Settings.


#include "APlatformSpawner.h"

// Sets default values
AAPlatformSpawner::AAPlatformSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAPlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPlatforms(AmountOfPlatformsToSpawn);
}

// Called every frame
void AAPlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAPlatformSpawner::SpawnPlatforms(uint8 InAmount)
{
	AActor* SpawnedPlatform = NULL;
	USceneComponent* ArrowComponent = NULL;
	FVector PlatformLocation;
	FVector NextSpawnLocation;

	for (size_t i = 0; i < InAmount; i++)
	{
		// Spawn platform and get the arrow component
		SpawnedPlatform = GetWorld()->SpawnActor<AActor>(Platform, FVector(), FRotator());
		ArrowComponent = SpawnedPlatform->GetRootComponent()->GetChildComponent(3);

		// Get platform's location
		PlatformLocation = SpawnedPlatform->GetActorLocation();

		// Set new platform's location 
		SpawnedPlatform->SetActorLocation(FVector(PlatformLocation.X, PlatformLocation.Y + NextSpawnLocation.Y, PlatformLocation.Z));
		NextSpawnLocation = ArrowComponent->GetComponentLocation();
	}
}
