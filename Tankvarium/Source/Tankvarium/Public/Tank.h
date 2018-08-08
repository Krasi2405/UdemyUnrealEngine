// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declarations
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;

UCLASS()
class TANKVARIUM_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();


public:	
	void AimAt(FVector AimLocation);

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetBarrelPointer(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretPointer(UTankTurret* TurretToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; // 1000 m/s default 


	UTankAimingComponent* TankAimingComponent = nullptr;
};
