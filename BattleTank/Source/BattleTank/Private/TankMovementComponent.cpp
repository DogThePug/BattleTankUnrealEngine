// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//This is done so it won`t override the IntendTurnRight in TankTrack when it is 0
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
}
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto RightThrowVector = FVector::CrossProduct(TankForwardDirection, AIForwardIntention);
	auto RightThrow = RightThrowVector.Z;
	IntendTurnRight(2*RightThrow);


	auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	
}
void UTankMovementComponent::IntendTurnRight(float Throw)
{
		LeftTrack->SetThrottle(2*Throw);
		RightTrack->SetThrottle(-2*Throw);

}

