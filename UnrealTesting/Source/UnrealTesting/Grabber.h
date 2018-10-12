// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALTESTING_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Attempt to configure Input component
	void SetupInputComponent();

	// Attempt to configure physics handle component
	void FindPhysicsHandleComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// Variables for player view location and rotation
	FVector Position;
	FRotator Rotation;

	// External editable variable for character reach length
	UPROPERTY(EditAnywhere)
		float Reach = 100.f;

	// Pointer for physics handle component
	UPhysicsHandleComponent* PhysicsHandler = nullptr;

	// Pointer for input component
	UInputComponent* InputComponent = nullptr;

	// Raycast and grab what is in reach
	void Grab();

	// Release what has been grabbed
	void Release();

	// Return raycast hit when grabbing for an object
	FHitResult GetFirstPhysicsBodyInReach();

	// Return ray endpoint
	FVector GetReachLineEndpoint();

};
