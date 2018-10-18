// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	
	virtual void BeginPlay() override;
	
	ATank* GetControlledTank() const;

	void AimTowardCrosshair();

	bool GetSightRayHitLocation(FVector&) const;
	
	ATankPlayerController();
	
	virtual void Tick(float) override;

	bool GetLookVectorHitLocation(FVector&, FVector) const;

	UPROPERTY(EditAnywhere)
		float LookDistance = 1000000.f;
	
	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f, CrossHairYLocation = 0.3333f;

};
