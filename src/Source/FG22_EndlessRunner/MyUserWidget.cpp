#include "MyUserWidget.h"

void UMyUserWidget::SetScoreText(uint32 InScore)
{
	Score->SetText(FText::AsNumber(InScore));
}

void UMyUserWidget::SetHealthText(uint32 InHealth)
{
	Health->SetText(FText::AsNumber(InHealth));
}