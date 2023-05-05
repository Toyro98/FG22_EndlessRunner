#include "UIMockupPlayerController.h"

void AUIMockupPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Widget = CreateWidget(this, WidgetClass);
	Widget->AddToViewport();

	FInputModeUIOnly Input;
	Input.SetWidgetToFocus(Widget->GetCachedWidget());
	Input.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	SetInputMode(Input);

	bShowMouseCursor = true;
}