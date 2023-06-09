// Copyright Epic Games, Inc. All Rights Reserved.

#include "FG22_EndlessRunnerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


//////////////////////////////////////////////////////////////////////////
// AFG22_EndlessRunnerCharacter

AFG22_EndlessRunnerCharacter::AFG22_EndlessRunnerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 700.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SocketOffset = FVector(320.0, 0.0, 192.0f);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->AddLocalRotation(FRotator(-35.0f, 0.0, 0.0));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AFG22_EndlessRunnerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();
	PlatformManager = Cast<AAPlatformManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAPlatformManager::StaticClass()));
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	// Add Input Mapping Context
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		FInputModeGameOnly Input;
		PlayerController->SetInputMode(Input);
	}

	// Hud
	if (PlayerHudClass)
	{
		PlayerHud = CreateWidget<UMyUserWidget>(PlayerController, PlayerHudClass);
		PlayerHud->AddToPlayerScreen();
		PlayerHud->SetHealthText(LivesLeft);
	}

	// Load save game and update the highscore
	// We do it here as then we know the playerhud has loaded
	PlatformManager->LoadGame();
	PlatformManager->PlayerHud = PlayerHud;

	uint32 HighScore = 0;

	if (PlatformManager->HighScores.Num() > 0)
	{
		HighScore = PlatformManager->HighScores[0];
	}

	PlatformManager->PlayerHud->SetHighScoreText(HighScore);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFG22_EndlessRunnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFG22_EndlessRunnerCharacter::Move);
	}
}

void AFG22_EndlessRunnerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(RightDirection, MovementVector.X);
		AddMovementInput(ForwardDirection, 1);
	}
}

void AFG22_EndlessRunnerCharacter::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	// Modified Move function to make the character always move forward
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// add movement 
		AddMovementInput(ForwardDirection, 1);
	}
}

void AFG22_EndlessRunnerCharacter::TakeDamage()
{
	LivesLeft--;

	if (LivesLeft <= 0)
	{
		PlatformManager->Reset();
		Reset();
	}
	else
	{
		PlayerHud->SetHealthText(LivesLeft);
	}
}

void AFG22_EndlessRunnerCharacter::IncreaseCharacterSpeed(float InAmount)
{
	GetCharacterMovement()->MaxWalkSpeed += InAmount;
}

void AFG22_EndlessRunnerCharacter::Reset()
{
	LivesLeft = 3;
	GetCharacterMovement()->MaxWalkSpeed = 700;
	SetActorLocation(SpawnLocation);

	PlayerHud->SetHealthText(LivesLeft);
}