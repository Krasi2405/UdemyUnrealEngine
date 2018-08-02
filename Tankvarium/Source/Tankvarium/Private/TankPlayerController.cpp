// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PossessedTank = GetControlledTank();
	if (PossessedTank) {
		UE_LOG(LogTemp,Warning, TEXT("tank possessed %s"), *PossessedTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController does not possess a tank"))
	}
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
