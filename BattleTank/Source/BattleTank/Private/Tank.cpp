// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//This is used to create inherited Aiming Component
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("%f damage to apply, Clamped from %f"), DamageToApply, DamageAmount);
	CurrentHealth -= DamageToApply;
	return DamageToApply;
}

float ATank::GetCurrentHealth()
{
	return CurrentHealth;
}












