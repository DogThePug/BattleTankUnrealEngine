// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank * ATankAIController::GetPlayerTank() const
{
	APawn * PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerTank);
}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank * ControlledTank = GetControlledTank();
	ATank * PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s player tank found"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank not found!"));
	}
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s ai calling"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ai calling doesn't have a tank"));
	}
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {
		// TODO Move towards player

		//Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation(), GetControlledTank()->LaunchSpeed);
	
		// Fire if ready
	}
}


