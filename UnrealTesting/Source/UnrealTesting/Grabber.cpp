// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty on %s"), *GetOwner()->GetName())
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Position, OUT Rotation);

	UE_LOG(LogTemp, Warning, TEXT("Position %s : Rotation %s"), *Position.ToString(), *Rotation.ToString());

	// Raycast from this view to a specified distance
	TraceEnd = Position + Rotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), Position, TraceEnd, FColor(255, 0, 0), false, 0.f, 0, 10.f);

	// Record what is hit

}

