#include "APlatformManager.h"
#include "APlatform.h"
#include "ERSaveGame.h"
#include "Kismet/GameplayStatics.h"

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
	TObjectPtr<AAPlatform> SpawnedPlatform = nullptr;
	TObjectPtr<USceneComponent> ArrowComponent = nullptr;
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

		SpawnedPlatforms.Add(SpawnedPlatform->GetRootComponent());
	}

	NextSpawnLocation = FVector(0.0, NextSpawnLocation.Y, 0.0);
}

void AAPlatformManager::MovePlatform(TObjectPtr<AActor> PlatformActor)
{
	PlatformActor->SetActorLocation(NextSpawnLocation);
	NextSpawnLocation = FVector(NextSpawnLocation.X, NextSpawnLocation.Y + PlatformSizeY, 0.0);

	TimeSinceLastPlatformTeleport = GetWorld()->TimeSeconds;

	Score++;
	PlayerHud->SetScoreText(Score);
}

void AAPlatformManager::SetVisibilityOnObstacle(TObjectPtr<AActor> PlatformActor)
{
	TObjectPtr<USceneComponent> Obstacles = PlatformActor->GetRootComponent()->GetChildComponent(1);

	for (size_t i = 0; i < Obstacles->GetNumChildrenComponents(); i++)
	{
		Obstacles->GetChildComponent(i)->SetVisibility(false, true);
	}

	uint32 Index = FMath::FRandRange(0, Obstacles->GetNumChildrenComponents());
	Obstacles->GetChildComponent(Index)->SetVisibility(true, true);
}

void AAPlatformManager::Reset()
{
	NextSpawnLocation = FVector().ZeroVector;
	TimeSinceLastPlatformTeleport = 0.0f;

	SaveGame();

	if (HighScores.Num() != 0)
	{
		if (Score >= HighScores[0])
		{
			PlayerHud->SetHighScoreText(HighScores[0]);
		}
	}

	for (size_t i = 0; i < SpawnedPlatforms.Num(); i++)
	{
		TObjectPtr<USceneComponent> Obstacles = SpawnedPlatforms[i]->GetChildComponent(1);

		for (size_t j = 0; j < Obstacles->GetNumChildrenComponents(); j++)
		{
			Obstacles->GetChildComponent(j)->SetVisibility(false, true);
		}

		MovePlatform(SpawnedPlatforms[i]->GetAttachmentRootActor());
	}

	Score = 0;
	PlayerHud->SetScoreText(Score);
}

static bool Compare(const uint32& a, const uint32& b)
{
	return a > b;
}

void AAPlatformManager::SaveGame()
{
	TObjectPtr<UERSaveGame> SaveGame = Cast<UERSaveGame>(UGameplayStatics::CreateSaveGameObject(UERSaveGame::StaticClass()));

	if (Score <= 0)
	{
		return;
	}

	if (HighScores.Num() != 10)
	{
		HighScores.Add(Score);
		Algo::Sort(HighScores, Compare);
	}
	else
	{
		for (int i = 9; i >= 0; i--)
		{
			if (HighScores[i] >= Score)
			{
				HighScores[i] = Score;
				break;
			}
		}
	}

	SaveGame->HighScores = HighScores;

	UGameplayStatics::SaveGameToSlot(SaveGame, SaveGame->SaveSlotName, 0);
}

void AAPlatformManager::LoadGame()
{
	TObjectPtr<UERSaveGame> SaveGame = Cast<UERSaveGame>(UGameplayStatics::CreateSaveGameObject(UERSaveGame::StaticClass()));
	SaveGame = Cast<UERSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGame->SaveSlotName, 0));

	if (SaveGame)
	{
		HighScores = SaveGame->HighScores;
	}
}