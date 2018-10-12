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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If physics handle attached
		// Move object we are holding
	if (!PhysicsHandler) { return; }

	if (PhysicsHandler->GrabbedComponent)
	{
		PhysicsHandler->SetTargetLocation(GetReachLineEndpoint());
	}

}

void UGrabber::Grab()
{
	// Try to reach any actor with physics body collision set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	if (HitResult.GetActor())
	{
		if (!PhysicsHandler) { return; }
		PhysicsHandler->GrabComponent(HitResult.GetComponent(), NAME_None, HitResult.GetActor()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandler) { return; }
	PhysicsHandler->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandler == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle not found on %s"), *GetOwner()->GetName());

	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		// Bind input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input handler not found on %s"), *GetOwner()->GetName());

	}
}

// Return hit for first physics body in reach
FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		Position,
		GetReachLineEndpoint(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;

}

FVector UGrabber::GetReachLineEndpoint()
{
	// Get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Position, OUT Rotation);

	// Raycast from this view to a specified distance
	FVector TraceEnd = Position + Rotation.Vector() * Reach;

	return TraceEnd;

}