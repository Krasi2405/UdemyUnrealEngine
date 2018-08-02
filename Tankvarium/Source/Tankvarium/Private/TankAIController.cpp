// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found tank "))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Pawn not found for TankAIController on %s"), *ControlledTank->GetName())
	}

}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
