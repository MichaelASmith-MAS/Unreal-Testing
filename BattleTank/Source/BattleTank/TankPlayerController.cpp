// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto TempTank = GetControlledTank();

	if (!TempTank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController has not possessed a tank"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing: %s"), *TempTank->GetName());

	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);

	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector CamPosition;
	FVector ViewDirection;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	FVector2D ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamPosition, ViewDirection))
	{
		return GetLookVectorHitLocation(OutHitLocation, ViewDirection);

	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &OutHitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult, 
			StartLocation, 
			StartLocation + (LookDirection * LookDistance), 
			ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;

	}

	return false;
}

