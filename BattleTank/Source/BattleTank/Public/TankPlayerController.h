// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
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
	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.3333333333333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
