// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "APlatformManager.h"
#include "MyUserWidget.h"
#include "FG22_EndlessRunnerCharacter.generated.h"

class AAPlatformMannager;

UCLASS(config=Game)
class AFG22_EndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

public:
	AFG22_EndlessRunnerCharacter();
	
	UPROPERTY(VisibleAnywhere)
	uint8 LivesLeft = 3;

	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AAPlatformManager> PlatformManager;

	UFUNCTION()
	void TakeDamage();

	UFUNCTION()
	void IncreaseCharacterSpeed(float InAmount);

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Reset() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMyUserWidget> PlayerHudClass;

	UPROPERTY()
	class UMyUserWidget* PlayerHud;
};

