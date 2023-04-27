#include "MyUserWidget.h"

void UMyUserWidget::SetScoreText(uint32 InScore)
{
	Score->Text = FText::AsNumber(InScore);
}

void UMyUserWidget::SetHealthText(uint32 InHealth)
{
	Health->Text = FText::AsNumber(InHealth);
}