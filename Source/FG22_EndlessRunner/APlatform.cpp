#include "APlatform.h"
#include "FG22_EndlessRunnerCharacter.h"

AAPlatform::AAPlatform()
{
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	SceneRootComponent->SetupAttachment(RootComponent);
	PlatformMeshComponent->SetupAttachment(SceneRootComponent);
	TriggerComponent->SetupAttachment(PlatformMeshComponent);

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AAPlatform::OnOverlapBegin);
}

void AAPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFG22_EndlessRunnerCharacter* Character = Cast<AFG22_EndlessRunnerCharacter>(OtherActor);

	if (!Character)
	{
		return;
	}

	if (GetWorld()->TimeSeconds - PlatformManager->TimeSinceLastPlatformTeleport > 0.1f)
	{
		PlatformManager->MovePlatform(this);
	}
}

void AAPlatform::SetPlatformManager(AAPlatformManager* InPlatformManager)
{
	PlatformManager = InPlatformManager;
}

