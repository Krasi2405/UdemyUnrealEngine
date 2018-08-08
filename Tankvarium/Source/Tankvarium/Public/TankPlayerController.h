// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKVARIUM_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	ATank* GetControlledTank() const;

	bool GetLookVectorHitLocation(FVector WorldDirection, FVector& HitLocation) const;
	
	void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void AimAtCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333333f;
	UPROPERTY(EditAnywhere)
		int32 Range = 1000000.f;
};
