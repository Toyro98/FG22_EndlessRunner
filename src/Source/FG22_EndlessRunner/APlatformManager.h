#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APlatformManager.generated.h"

UCLASS()
class FG22_ENDLESSRUNNER_API AAPlatformManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAPlatformManager();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Platform;

	UPROPERTY(VisibleAnywhere)
	TArray<USceneComponent*> SpawnedPlatforms;

	UPROPERTY(EditAnywhere)
	uint8 AmountOfPlatformsToSpawn = 6;

	UPROPERTY(VisibleAnywhere)
	FVector NextSpawnLocation = FVector();

	UPROPERTY(VisibleAnywhere)
	float TimeSinceLastPlatformTeleport = 0.0f;

	UPROPERTY(VisibleAnywhere)
	float PlatformSizeY = 0.0f;

	void MovePlatform(AActor* PlatformActor);

	void SpawnPlatforms(uint8 InAmount);

	void SetVisibilityOnObstacle(AActor* PlatformActor);

	void ResetManager();

protected:
	virtual void BeginPlay() override;

	virtual void Reset() override;
};