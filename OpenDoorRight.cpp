// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorRight.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoorRight::UOpenDoorRight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorRight::BeginPlay()
{
	Super::BeginPlay();

	InitialYawRight = GetOwner()->GetActorRotation().Yaw;
	CurrentYawRight = InitialYawRight;
	OpenAngleRight += InitialYawRight; // OpenAngle = OpenAngle + InitialYaw;

	FindAudioComponentRight();
}

void UOpenDoorRight::FindAudioComponentRight()
{
	AudioComponentRight = GetOwner()->FindComponentByClass<UAudioComponent>();
}


// Called every frame
void UOpenDoorRight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActorsRight() > MassToOpenDoorRight)
	{
		OpenRightDoor(DeltaTime);
		DoorLastOpenRight = GetWorld()->GetTimeSeconds();
	}

	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpenRight > DoorCloseDelayRight)
		{
			CloseRightDoor(DeltaTime);
		}
	}

	GetWorld()->GetTimeSeconds();
}

void UOpenDoorRight::OpenRightDoor(float DeltaTime)
{
	CurrentYawRight = FMath::Lerp(CurrentYawRight, OpenAngleRight, DeltaTime * DoorOpenSpeedRight);

	FRotator DoorRotationRight = GetOwner()->GetActorRotation();

	DoorRotationRight.Yaw =  CurrentYawRight;
	GetOwner()->SetActorRotation(DoorRotationRight);

	CloseDoorSoundRight = false;
	if(!AudioComponentRight){return;}
	if(!OpenDoorSoundRight)
	{
		AudioComponentRight->Play();
		OpenDoorSoundRight = true;
	}
}

void UOpenDoorRight::CloseRightDoor(float DeltaTime)
{
	CurrentYawRight = FMath::Lerp(CurrentYawRight, OpenAngleRight, DeltaTime * DoorOpenSpeedRight);
	
	FRotator DoorRotationRight = GetOwner()->GetActorRotation();

	DoorRotationRight.Yaw =  CurrentYawRight;
	GetOwner()->SetActorRotation(DoorRotationRight);

	OpenDoorSoundRight = false;
	if(!AudioComponentRight){return;}
	if(!CloseDoorSoundRight)
	{
		AudioComponentRight->Play();
		CloseDoorSoundRight = true;
	}
}

float UOpenDoorRight::TotalMassOfActorsRight() const
{
	float TotalMass = 0.f;

	// Find All Overlapping Actors
	TArray<AActor*> OverlappingActors;
	if(!PressurePlate1){return TotalMass;}
	PressurePlate1->GetOverlappingActors(OUT OverlappingActors);

	// Add up Thier Masses
	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
