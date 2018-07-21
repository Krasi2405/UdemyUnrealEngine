// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"
#define OUT

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	return LineTraceEnd;
}

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();

}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent) {
		float PlayerYaw = FPlayerOrientation.PlayerViewPointRotation.Yaw; // The player's Yaw is updated here.
		float NewYaw = (PlayerYaw - PlayerCapturedYaw) + GrabbedCapturedYaw; // Your changes in rotation are added to the grabbed object.

		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
		PhysicsHandle->SetTargetRotation(FRotator(0.0f, NewYaw, 0.0f));

	}
	// ...
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle component not found on object %s"), *GetOwner()->GetName());
	}
	else {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle component not found on object %s"), *GetOwner()->GetName());
	}
}

// Called every frame


FHitResult UGrabber::GetFirstHitTarget()
{

	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		FPlayerOrientation.PlayerViewPointLocation,
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab"));

	FHitResult HitResult =  GetFirstHitTarget();
	AActor* ActorHit = HitResult.GetActor();
	UPrimitiveComponent* Component = HitResult.GetComponent();

	if (ActorHit && Component) {
		GrabbedCapturedYaw = ActorHit->GetActorRotation().Yaw;
		PlayerCapturedYaw = FPlayerOrientation.PlayerViewPointRotation.Yaw;
		PhysicsHandle->GrabComponentAtLocation(
			Component,
			NAME_None,
			Component->GetOwner()->GetActorLocation()
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release"));
	PhysicsHandle->ReleaseComponent();
}