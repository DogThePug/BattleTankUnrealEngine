// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class ATank;
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
private:
	bool GetLookVectorHitLocation(FHitResult& HitResult, FVector LookDirection) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	ATank * GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairLocationX = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairLocationY = 0.3333333333333;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
};
