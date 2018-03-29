// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void ElevateBarrel ( float RelativeSpeed);
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 5;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationDegrees = 40;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevetionDegrees = 0;
};
