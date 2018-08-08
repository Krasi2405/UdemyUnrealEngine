// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned


void ATank::AimAt(FVector AimLocation)
{
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
	
}

void ATank::SetBarrelPointer(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelPointer(BarrelToSet);
}

void ATank::SetTurretPointer(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretPointer(TurretToSet);
}
