#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenu.generated.h"

UCLASS()
class FG22_ENDLESSRUNNER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UButton> StartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> HighScoreText;

protected:

	UFUNCTION()
	void OnButtonClicked();

	void NativeConstruct() override;
};
