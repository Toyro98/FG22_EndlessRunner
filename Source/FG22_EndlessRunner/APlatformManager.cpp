#include "APlatformManager.h"
#include "APlatform.h"

AAPlatformManager::AAPlatformManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAPlatformManager::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPlatforms(AmountOfPlatformsToSpawn);
}

void AAPlatformManager::SpawnPlatforms(uint8 InAmount)
{
	AAPlatform* SpawnedPlatform = nullptr;
	USceneComponent* ArrowComponent = nullptr;
	FVector PlatformLocation;

	for (size_t i = 0; i < InAmount; i++)
	{
		SpawnedPlatform = GetWorld()->SpawnActor<AAPlatform>(Platform, FVector(), FRotator());
		ArrowComponent = SpawnedPlatform->GetRootComponent()->GetChildComponent(0)->GetChildComponent(3);

		SpawnedPlatform->SetPlatformManager(this);
		PlatformLocation = SpawnedPlatform->GetActorLocation();

		SpawnedPlatform->SetActorLocation(FVector(PlatformLocation.X, PlatformLocation.Y + NextSpawnLocation.Y, PlatformLocation.Z));
		NextSpawnLocation = ArrowComponent->GetComponentLocation();

		if (i == 0)
		{
			PlatformSizeY = ArrowComponent->GetComponentLocation().Y;
		}
	}

	NextSpawnLocation = FVector(0.0, NextSpawnLocation.Y, 0.0);
}

void AAPlatformManager::MovePlatform(AActor* PlatformActor)
{
	PlatformActor->SetActorLocation(NextSpawnLocation);
	NextSpawnLocation = FVector(NextSpawnLocation.X, NextSpawnLocation.Y + PlatformSizeY, NextSpawnLocation.Z);

	TimeSinceLastPlatformTeleport = GetWorld()->TimeSeconds;
}