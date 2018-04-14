// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	void Tick(float DeltaTime) override;
private:
	//How close can enemy tank come to player
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 5000;
	void BeginPlay() override;
	
};
