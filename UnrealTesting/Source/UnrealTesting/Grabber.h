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

	void SetupInputComponent();

	void FindPhysicsHandleComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FVector Position;
	FRotator Rotation;

	UPROPERTY(EditAnywhere)
		float Reach = 100.f;

	FVector TraceEnd;
	
	UPhysicsHandleComponent* PhysicsHandler = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Raycast and grab what is in reach
	void Grab();

	// Release what has been grabbed
	void Release();

	FHitResult GetFirstPhysicsBodyInReach();

};
