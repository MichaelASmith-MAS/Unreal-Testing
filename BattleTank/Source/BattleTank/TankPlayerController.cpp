// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


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
		UE_LOG(LogTemp, Warning, TEXT("%s possessed"), *TempTank->GetName());

	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}
