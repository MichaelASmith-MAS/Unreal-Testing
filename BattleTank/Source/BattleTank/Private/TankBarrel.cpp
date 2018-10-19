// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto ElevationChange = FMath::Clamp(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto ClampedElevation = FMath::Clamp(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);
	
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

}


