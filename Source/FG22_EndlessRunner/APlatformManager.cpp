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

		SpawnedPlatform->SetActorLocation(FVector(PlatformLocation.X, PlatformLocation.Y + NextSpawnLocation.Y, 0.0));
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
	NextSpawnLocation = FVector(NextSpawnLocation.X, NextSpawnLocation.Y + PlatformSizeY, 0.0);

	TimeSinceLastPlatformTeleport = GetWorld()->TimeSeconds;
}

void AAPlatformManager::SetVisibilityOnObstacle(AActor* PlatformActor)
{
	USceneComponent* Obstacles = PlatformActor->GetRootComponent()->GetChildComponent(1);

	for (size_t i = 0; i < Obstacles->GetNumChildrenComponents(); i++)
	{
		Obstacles->GetChildComponent(i)->SetVisibility(false, true);
	}

	uint32 Index = FMath::FRandRange(0, Obstacles->GetNumChildrenComponents());
	Obstacles->GetChildComponent(Index)->SetVisibility(true, true);
}

void AAPlatformManager::ResetManager()
{
	Reset();
}

void AAPlatformManager::Reset()
{
	NextSpawnLocation = FVector().ZeroVector;
	TimeSinceLastPlatformTeleport = 0.0f;

	for (size_t i = 0; i < SpawnedPlatforms.Num(); i++)
	{
		// Hide all 
		USceneComponent* Obstacles = SpawnedPlatforms[i]->GetChildComponent(1);

		for (size_t j = 0; j < Obstacles->GetNumChildrenComponents(); j++)
		{
			Obstacles->GetChildComponent(j)->SetVisibility(false, true);
		}

		MovePlatform(SpawnedPlatforms[i]->GetAttachmentRootActor());
	}
}