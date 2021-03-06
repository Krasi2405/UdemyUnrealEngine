// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupInputComponent();

	void FindPhysicsHandleComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;
		
	FHitResult GetFirstHitTarget();

	void Grab();

	void Release();

	struct FPlayerOrientation {
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
	} FPlayerOrientation;

	FVector GetReachLineEnd();


	float GrabbedCapturedYaw = 0.0f; // Yaw of the Grabbed item is captured here the moment it's grabbed.
	float PlayerCapturedYaw = 0.0f; // Yaw of the Player is captured here the moment you grab something.
	
};
