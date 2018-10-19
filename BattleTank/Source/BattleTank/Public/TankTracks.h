// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * TankTrack is used to set maximum drive speed and apply forces to tank.
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	
private:
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000.f;


};
