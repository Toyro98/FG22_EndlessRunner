#include "UIMockupPlayerController.h"

void AUIMockupPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Widget = CreateWidget(this, WidgetClass);
	Widget->AddToViewport();
}