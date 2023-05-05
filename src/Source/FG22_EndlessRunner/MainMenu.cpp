#include "MainMenu.h"
#include "ERSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	StartButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OnButtonClicked);

	// Load Savegame
	TObjectPtr<UERSaveGame> SaveGame = Cast<UERSaveGame>(UGameplayStatics::CreateSaveGameObject(UERSaveGame::StaticClass()));
	SaveGame = Cast<UERSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGame->SaveSlotName, 0));

	FString text = "";

	if (SaveGame)
	{
		for (int i = 0; i < SaveGame->HighScores.Num(); i++)
		{
			text += FString::FromInt(SaveGame->HighScores[i]) + "\n";
		}
	}
	else
	{
		text = "No highscore could be found";
	}

	HighScoreText->SetText(FText::FromString(text));
}

void UMainMenu::OnButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "ThirdPersonMap");
}
