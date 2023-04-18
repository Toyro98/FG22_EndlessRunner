#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "APlatformManager.h"
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
	USceneComponent* SceneRootComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetPlatformManager(AAPlatformManager* InPlatformManager);

private:
	class AAPlatformManager* PlatformManager = nullptr;
};
