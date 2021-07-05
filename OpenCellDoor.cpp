// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCellDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT


// Sets default values for this component's properties
UOpenCellDoor::UOpenCellDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenCellDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYawCell = GetOwner()->GetActorRotation().Yaw;
	CurrentYawCell = InitialYawCell;
	OpenAngleCell += InitialYawCell; // OpenAngle = OpenAngle + InitialYaw;

	FindAudioComponentCell();
}

void UOpenCellDoor::FindAudioComponentCell()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}


// Called every frame
void UOpenCellDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActorsCell() > MassToOpenDoor)
	{
		OpenCellDoor(DeltaTime);
		DoorLastOpenCell = GetWorld()->GetTimeSeconds();
	}

	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpenCell > DoorCloseDelayCell)
		{
			CloseCellDoor(DeltaTime);
		}
	}

	GetWorld()->GetTimeSeconds();
}

void UOpenCellDoor::OpenCellDoor(float DeltaTime)
{
	CurrentYawCell = FMath::Lerp(CurrentYawCell, OpenAngleCell, DeltaTime * DoorOpenSpeedCell);

	FRotator DoorRotation = GetOwner()->GetActorRotation();

	DoorRotation.Yaw = CurrentYawCell;
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSoundCell = false;
	if(!AudioComponent){return;}
	if(!OpenDoorSoundCell)
	{
		AudioComponent->Play();
		OpenDoorSoundCell = true;
	}
}

void UOpenCellDoor::CloseCellDoor(float DeltaTime)
{
	CurrentYawCell = FMath::Lerp(CurrentYawCell, OpenAngleCell, DeltaTime * DoorOpenSpeedCell);
	
	FRotator DoorRotation = GetOwner()->GetActorRotation();

	DoorRotation.Yaw = CurrentYawCell;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSoundCell = false;
	if(!AudioComponent){return;}
	if(!CloseDoorSoundCell)
	{
		AudioComponent->Play();
		CloseDoorSoundCell = true;
	}
}

float UOpenCellDoor::TotalMassOfActorsCell() const
{
	float TotalMass = 0.f;

	// Find All Overlapping Actors
	TArray<AActor*> OverlappingActors;
	if(!PressurePlate2){return TotalMass;}
	PressurePlate2->GetOverlappingActors(OUT OverlappingActors);

	// Add up Thier Masses
	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
