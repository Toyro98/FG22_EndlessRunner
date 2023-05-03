#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UIMockupPlayerController.generated.h"

UCLASS()
class FG22_ENDLESSRUNNER_API AUIMockupPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UUserWidget> Widget;

protected:
	void BeginPlay() override;
};
