#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "APlatformManager.h"
#include "Obstacle.h"
#include "APlatform.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class FG22_ENDLESSRUNNER_API AAPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AAPlatform();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneRootComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> PlatformMeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Obstacles;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> TriggerComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetPlatformManager(TObjectPtr<AAPlatformManager> InPlatformManager);

private:
	TObjectPtr<class AAPlatformManager> PlatformManager = nullptr;
};
