// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	UE_LOG(LogTemp, Warning, TEXT("%f barrel elevate called with speed %f"), GetWorld()->GetTimeSeconds(), RelativeSpeed)

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float RotationPerFrame = RelativeSpeed * MaxElevationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Elevation = RelativeRotation.Pitch + RotationPerFrame;
	float ClampedElevation = FMath::Clamp<float>(Elevation, MinElevationDegrees, MaxElevationDegrees);
	
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
	
}


