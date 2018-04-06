// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float ProjectileSpeed)
{
	
	if (!Barrel || !TankTurret) return;
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FiringPoint"));
	/// Calculate the launch velocity (launch vector)
	TArray<AActor*> ActorsToIgnore;
	bool bSolutionFound = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		ProjectileSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
		if(bSolutionFound) 
		{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		}
}
void UTankAimingComponent::Initialise(UTankBarrel * TankBarrelToSet, UTurret * TurretToSet)
{
	Barrel = TankBarrelToSet;
	TankTurret = TurretToSet;
}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel) return;
	// Work out a difference between corrent barrel rotation and AimDirection
	auto DeltaRotation = FindDifferenceInRotation(Barrel, AimDirection);
	//Move the barrel the right amount this frame
	Barrel->ElevateBarrel(DeltaRotation.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto DeltaRotation = FindDifferenceInRotation(TankTurret, AimDirection);
	TankTurret->RotateTurret(DeltaRotation.Yaw);
}

FRotator UTankAimingComponent::FindDifferenceInRotation(UTankBarrel * Barrel, FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;
	return DeltaRotation;
}
FRotator UTankAimingComponent::FindDifferenceInRotation(UTurret * Turret, FVector AimDirection)
{
	auto BarrelRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;
	return DeltaRotation;
}
