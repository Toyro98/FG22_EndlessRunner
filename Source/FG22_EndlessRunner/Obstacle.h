#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Obstacle.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS(Blueprintable, ClassGroup = (Rendering, Common), meta = (BlueprintSpawnableComponent))
class FG22_ENDLESSRUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObstacleMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
