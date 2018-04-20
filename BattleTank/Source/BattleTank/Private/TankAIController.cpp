// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Classes/AIController.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn * PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank`s death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}
void ATankAIController::OnPossessedTankDeath()
{
	if (GetPawn()) {
		auto PossessedTank = Cast<ATank>(GetPawn());
		PossessedTank->DetachFromControllerPendingDestroy();
	}
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn * PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (PlayerTank && ControlledTank) {
		//Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);
		//Aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
		if(AimingComponent->GetFiringState() == EFiringState::Locked)
		AimingComponent->Fire();
	}
}


