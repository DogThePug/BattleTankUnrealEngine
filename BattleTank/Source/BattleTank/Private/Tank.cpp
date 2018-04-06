// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//This is used to create inherited Aiming Component
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetupAimingComponent(UTankAimingComponent * AimingComponent)
{
	TankAimingComponent = AimingComponent;
}

void ATank::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!TankAimingComponent)return;
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}





void ATank::Fire()
{
	if (!ProjectileBlueprint) 
	{
	UE_LOG(LogTemp, Error, TEXT("Tank doesn't have projectile set up!"));
	return;
	}
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (Barrel && bIsReloaded) {

	// Spawn some dood to fly sky high
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("FiringPoint")),
		Barrel->GetSocketRotation(FName("FiringPoint"))
		);
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}
}


