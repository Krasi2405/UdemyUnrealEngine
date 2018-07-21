// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"
#define OUT
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
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);


	//UE_LOG(LogTemp, Warning, TEXT("Reporting position: %s and rotation %s, rotationVector: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString(), *PlayerViewPointRotation.Vector().ToString());
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
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
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT FPlayerOrientation.PlayerViewPointLocation,
		OUT FPlayerOrientation.PlayerViewPointRotation);


	//UE_LOG(LogTemp, Warning, TEXT("Reporting position: %s and rotation %s, rotationVector: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString(), *PlayerViewPointRotation.Vector().ToString());
	FVector LineTraceEnd = FPlayerOrientation.PlayerViewPointLocation + FPlayerOrientation.PlayerViewPointRotation.Vector() * Reach;

	/*DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(120, 120, 120),
		false,
		0.f,
		0,
		10.f
	);*/

	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		FPlayerOrientation.PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		//UE_LOG(LogTemp, Warning, TEXT("Actor hit %s "), *ActorHit->GetName());
	}
	return Hit;
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab"));
	FHitResult HitResult =  GetFirstHitTarget();
	AActor* ActorHit = HitResult.GetActor();
	UPrimitiveComponent* Component = HitResult.GetComponent();
	if (ActorHit && Component) {
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