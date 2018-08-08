// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/*
 Holds properties and methods for the tank's barrel 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hideCategories= ("Collision"))
class TANKVARIUM_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditAnywhere)
	float MaxElevationDegreesPerSecond = 10;

	UPROPERTY(EditAnywhere)
	float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere)
	float MinElevationDegrees = 0;
	
};
