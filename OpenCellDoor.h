// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenCellDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MY_BUILDING_ESCAPE_API UOpenCellDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenCellDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenCellDoor(float DeltaTime);
	void CloseCellDoor(float DeltaTime);
	float TotalMassOfActorsCell() const;
	void FindAudioComponentCell();

	bool OpenDoorSoundCell = false;
	bool CloseDoorSoundCell = true;

private:
	
	float InitialYawCell;
	float CurrentYawCell;
	

	UPROPERTY(EditAnywhere)
	float OpenAngleCell = 90.f;

	float DoorLastOpenCell = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelayCell = .5f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeedCell = .8f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeedCell = 2.f;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate2 = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
		
};
