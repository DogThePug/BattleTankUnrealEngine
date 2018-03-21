// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"


ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Tank found"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank not found"));
	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	/// Aim towards crosshair 
}
void ATankPlayerController::AimTowardsCrosshair()
{
	if(!GetControlledTank()) return;

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation, GetControlledTank()->LaunchSpeed);
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
	}
	
	
	

	HitLocation = HitResult.Location;
	return true;
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
