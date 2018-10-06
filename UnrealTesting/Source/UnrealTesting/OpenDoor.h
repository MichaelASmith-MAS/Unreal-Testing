// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALTESTING_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	AActor* Owner;

	UPROPERTY(VisibleAnywhere)
		AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
		float OpenAngle = 60.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	
	UPROPERTY(VisibleAnywhere)
		bool bIsOpen;

	UPROPERTY(EditAnywhere)
		float TimeToClose = 1.f;

	UPROPERTY(VisibleAnywhere)
		float LastDoorOpenTime = 0.f;

};
