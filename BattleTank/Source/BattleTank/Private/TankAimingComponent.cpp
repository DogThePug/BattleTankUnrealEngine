// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Engine/World.h"
#include "Projectile.h"
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

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

bool UTankAimingComponent::BarrelIsMoving()
{
	if(AimDirection.Equals(Barrel->GetForwardVector().GetSafeNormal(), 0.1))
	return false;
	else return true;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (NumberOfMaxShots == 0) {
		FiringState = EFiringState::OutOfAmmo;
	}else
	if (!bIsReloaded) {
		FiringState = EFiringState::Reloading;
	}
	else if (BarrelIsMoving()) { FiringState = EFiringState::Aiming; }
	else {
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	
	if (!ensure(Barrel && TankTurret)) return;
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
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
		if(bSolutionFound) 
		{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		
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
	if (!ensure(Barrel)) return;
	// Work out a difference between corrent barrel rotation and AimDirection
	auto DeltaRotation = FindDifferenceInRotation(Barrel, AimDirection);
	//Move the barrel the right amount this frame
	Barrel->ElevateBarrel(DeltaRotation.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto DeltaRotation = FindDifferenceInRotation(TankTurret, AimDirection);
	if (FMath::Abs(DeltaRotation.Yaw)<180)
	TankTurret->RotateTurret(DeltaRotation.Yaw);
	else TankTurret->RotateTurret(-DeltaRotation.Yaw);
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
void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileBlueprint))
	{
		return;
	}
	if (!ensure(Barrel)) {
		return;
	}

	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo) {

		// Spawn some dood to fly sky high
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("FiringPoint")),
			Barrel->GetSocketRotation(FName("FiringPoint"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		NumberOfMaxShots--;
	}

}
EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}
int UTankAimingComponent::GetAmmoLeft()
{
	return NumberOfMaxShots;
}
