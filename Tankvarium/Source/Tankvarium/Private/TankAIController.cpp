// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found  player tank "))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController could not find player tank %s"), *PlayerTank->GetName())
	}

	ATank* PossessedTank = GetControlledTank();
	if (PossessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("tank possessed %s"), *PossessedTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController does not possess a tank"))
	}
}

ATank * ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) return nullptr;
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank) {

		//TODO move towards the player

		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		//fire if ready
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not find player tank"))
	}


}



ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
