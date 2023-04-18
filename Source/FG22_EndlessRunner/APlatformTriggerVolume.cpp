// Fill out your copyright notice in the Description page of Project Settings.


#include "APlatformTriggerVolume.h"

// Sets default values
AAPlatformTriggerVolume::AAPlatformTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; 
}

// Called when the game starts or when spawned
void AAPlatformTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}