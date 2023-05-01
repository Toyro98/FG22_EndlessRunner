#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ERSaveGame.generated.h"

UCLASS()
class FG22_ENDLESSRUNNER_API UERSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UERSaveGame();

	UPROPERTY(VisibleAnywhere)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere)
	uint32 HighScore;
};
