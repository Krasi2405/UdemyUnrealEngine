// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (Barrel) {
		UE_LOG(LogTemp, Warning, TEXT("aiming"))
			FString TankName = GetOwner()->GetName();
		FVector BarrelLocation = Barrel->GetSocketLocation(FName("Fire"));

		FVector OutLaunchVelocity;
		if (UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLaunchVelocity,
			BarrelLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			FCollisionResponseParams::DefaultResponseParam,
			TArray<AActor*>(),
			false
		)
			)
		{


		}
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from barrel location: %s"), *TankName, *AimDirection.ToString(), *BarrelLocation.ToString())
	}
}

void UTankAimingComponent::SetBarrelPointer(UStaticMeshComponent* BarrelToSet)
{

	this->Barrel = BarrelToSet;
	FString TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s barrel set"), *TankName)
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

