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
	Reloading,
	OutOfAmmo
};
class AProjectile;
class UTankBarrel;
class UTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 NumberOfMaxShots = 5;
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector WorldSpaceAim);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* TankBarrelToSet, UTurret* TurretToSet);
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000;

	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable)
	int GetAmmoLeft();
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ReloadTime = 3;
	EFiringState GetFiringState() const;
private:
	FVector AimDirection;
	bool BarrelIsMoving();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	double LastFireTime = 0;
	UTankBarrel * Barrel = nullptr;
	UTurret * TankTurret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	FRotator FindDifferenceInRotation(UTankBarrel* Barrel, FVector AimDirection);
	FRotator FindDifferenceInRotation(UTurret* Turret, FVector AimDirection);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;
};
