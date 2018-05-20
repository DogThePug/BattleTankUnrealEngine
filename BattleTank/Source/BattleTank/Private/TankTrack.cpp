// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	
}

void UTankTrack::SetThrottle(float Throttle)
{
	float ClampedThrottle = FMath::Clamp<float>(Throttle,-1.f,1.f);
	// Drive the tracks
	DriveTracks(ClampedThrottle);
}
TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultingArray;

	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultingArray.Add(SprungWheel);
	}
	return ResultingArray;
}
void UTankTrack::DriveTracks(float ClampedThrottle)
{
	auto ForceApplied = ClampedThrottle*TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* wheel : Wheels) {
		wheel->AddDrivingForce(ForcePerWheel);
	}
}

