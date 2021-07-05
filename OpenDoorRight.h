// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoorRight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MY_BUILDING_ESCAPE_API UOpenDoorRight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorRight();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenRightDoor(float DeltaTime);
	void CloseRightDoor(float DeltaTime);
	float TotalMassOfActorsRight() const;
	void FindAudioComponentRight();
	
	

	
	bool OpenDoorSoundRight = false;
	bool CloseDoorSoundRight = true;

private:

	float InitialYawRight;
	float CurrentYawRight;
	
	UPROPERTY(EditAnywhere)
	float OpenAngleRight = -90.f;

	float DoorLastOpenRight = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelayRight = .5f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeedRight = .8f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeedRight = 2.f;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoorRight = 50.f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate1 = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponentRight = nullptr;
};
