// Fill out your copyright notice in the Description page of Project Settings.
#include"Engine/World.h"
#include "Turret.h"

void UTurret::RotateTurret(float RelativeSpeed)
{
	auto ActualSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = ActualSpeed * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0,NewRotation,0));
}
