// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Classes/AIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn * PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn * PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(PlayerTank && ControlledTank)) {
		// TODO Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);
		//Aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
		// Fire if ready
		//ControlledTank->Fire();
	}
}


