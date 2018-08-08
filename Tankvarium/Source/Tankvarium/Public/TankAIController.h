// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TANKVARIUM_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	ATank* GetControlledTank() const;
	
	void BeginPlay() override;
	
	ATank* GetPlayerTank() const;

	virtual void Tick(float DeltaTime) override;
};
