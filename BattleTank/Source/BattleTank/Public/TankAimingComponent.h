// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

class UTankBarrel;
class UTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector WorldSpaceAim);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* TankBarrelToSet, UTurret* TurretToSet);
private:
	UTankBarrel * Barrel = nullptr;
	UTurret * TankTurret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	FRotator FindDifferenceInRotation(UTankBarrel* Barrel, FVector AimDirection);
	FRotator FindDifferenceInRotation(UTurret* Turret, FVector AimDirection);
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ProjectileSpeed = 4500;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;
};
