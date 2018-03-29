// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn * PlayerTankPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank * ControlledTank = Cast<ATank>(GetPawn());
	ATank * PlayerTank = Cast<ATank>(PlayerTankPawn);
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank * ControlledTank = Cast<ATank>(GetPawn());
	ATank * PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank) {
		// TODO Move towards player

		//Aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation(), ControlledTank->LaunchSpeed);
	
		// Fire if ready
		ControlledTank->Fire();
	}
}


