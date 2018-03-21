// Fill out your copyright notice in the Description page of Project Settings.
 
#include "TankBarrel.h"
#include "Engine/World.h"
void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	/// Move the barrel to the right amount this frame
	auto ActualSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto ElevationChange = ActualSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto NewElevation = FMath::Clamp(RawNewElevation, MinElevetionDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}


