// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) FoundAimingComponent(AimingComponent);
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	/// Aim towards crosshair 
}
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
	}
	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
		///Get World Location of linetrace throught crosshair	
		/// if it hits the landscape
		 /// Tell the barrel to aim there
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find Crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairLocationX, ViewportSizeY*CrosshairLocationY);
	//De-project screen position of the crosshair 
	FVector LookDirection;
	FHitResult HitResult;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along that look direction and see what we hit
		GetLookVectorHitLocation(HitResult, LookDirection);
		if (HitResult.Location == FVector(0, 0, 0))
		return false;
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}

ATank * ATankPlayerController::GetOwningTank()
{
	return Cast<ATank>(GetPawn());
}



bool ATankPlayerController::GetLookVectorHitLocation(FHitResult & HitResult, FVector LookDirection) const
{

	FVector LineEnd = LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		PlayerCameraManager->GetCameraLocation(), // the location of player camera
		PlayerCameraManager->GetCameraLocation() + LineEnd,
		ECollisionChannel::ECC_Visibility
	))
	return true;

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
	
}
