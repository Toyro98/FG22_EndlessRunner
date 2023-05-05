#include "Obstacle.h"
#include "FG22_EndlessRunnerCharacter.h"

AObstacle::AObstacle()
{
	ObstacleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle"));
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	ObstacleMeshComponent->SetupAttachment(RootComponent);
	TriggerComponent->SetupAttachment(ObstacleMeshComponent);

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnOverlapBegin);
}

void AObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<AFG22_EndlessRunnerCharacter> Character = Cast<AFG22_EndlessRunnerCharacter>(OtherActor);

	if (Character && ObstacleMeshComponent->IsVisible())
	{
		FString ScoreText = Character->PlayerHud->Score->GetText().ToString();
		uint32 Score = FCString::Atoi(*ScoreText);

		if (Score >= 6)
		{
			Character->TakeDamage();
		}
	}
}

