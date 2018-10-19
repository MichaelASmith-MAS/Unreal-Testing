// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	
	FVector OutLaunchVelocity = FVector(0.f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	auto Time = GetWorld()->GetTimeSeconds();
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrelToward(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%f: No aim solution found."), Time);
		MoveBarrelToward(FVector(0.f));

	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;

}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().ToOrientationRotator();
	auto AimAsRotator = AimDirection.ToOrientationRotator();

	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

}
