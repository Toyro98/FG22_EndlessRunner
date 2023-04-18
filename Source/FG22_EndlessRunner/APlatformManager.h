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

	UPROPERTY(EditAnywhere)
	uint8 AmountOfPlatformsToSpawn = 6;

	UPROPERTY(VisibleAnywhere)
	FVector NextSpawnLocation = FVector();

	UPROPERTY(VisibleAnywhere)
	double TimeSinceLastPlatformTeleport = 0.0f;

	UPROPERTY(VisibleAnywhere)
	double PlatformSizeY = 0.0f;

	void MovePlatform(AActor* PlatformActor);

protected:
	virtual void BeginPlay() override;

	void SpawnPlatforms(uint8 InAmount);
};
