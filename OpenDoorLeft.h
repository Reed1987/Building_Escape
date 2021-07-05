// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoorLeft.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MY_BUILDING_ESCAPE_API UOpenDoorLeft : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorLeft();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenLeftDoor(float DeltaTime);
	void CloseLeftDoor(float DeltaTime);
	float TotalMassOfActorsLeft() const;
	void FindAudioComponentLeft();
	// void PushButton();
	

	
	bool OpenDoorSoundLeft = false;
	bool CloseDoorSoundLeft = true;

private:
	
	float InitialYawLeft;
	float CurrentYawLeft;
	

	UPROPERTY(EditAnywhere)
	float OpenAngleLeft = 90.f;

	float DoorLastOpenLeft = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelayLeft = .5f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeedLeft = .8f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeedLeft = 2.f;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoorLeft = 50.f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate1 = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponentLeft = nullptr;
		
};
