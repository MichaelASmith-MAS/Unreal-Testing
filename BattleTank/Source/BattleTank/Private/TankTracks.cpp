// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"


void UTankTracks::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	UE_LOG(LogTemp, Warning, TEXT("%f throttle applied to %s"), Throttle, *GetName()); // TODO Clamp input

}

