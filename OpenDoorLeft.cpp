// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorLeft.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoorLeft::UOpenDoorLeft()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorLeft::BeginPlay()
{
	Super::BeginPlay();

	InitialYawLeft = GetOwner()->GetActorRotation().Yaw;
	CurrentYawLeft = InitialYawLeft;
	OpenAngleLeft += InitialYawLeft; // OpenAngle = OpenAngle + InitialYaw;

	FindAudioComponentLeft();
}

void UOpenDoorLeft::FindAudioComponentLeft()
{
	AudioComponentLeft = GetOwner()->FindComponentByClass<UAudioComponent>();
}


// Called every frame
void UOpenDoorLeft::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActorsLeft() > MassToOpenDoorLeft)
	{
		OpenLeftDoor(DeltaTime);
		// PushButton();
		DoorLastOpenLeft = GetWorld()->GetTimeSeconds();
	}

	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpenLeft > DoorCloseDelayLeft)
		{
			CloseLeftDoor(DeltaTime);
		}
	}

	GetWorld()->GetTimeSeconds();
}

void UOpenDoorLeft::OpenLeftDoor(float DeltaTime)
{
	CurrentYawLeft = FMath::Lerp(CurrentYawLeft, OpenAngleLeft, DeltaTime * DoorOpenSpeedLeft);

	FRotator DoorRotationLeft = GetOwner()->GetActorRotation();

	DoorRotationLeft.Yaw = CurrentYawLeft;
	GetOwner()->SetActorRotation(DoorRotationLeft);

	CloseDoorSoundLeft = false;
	if(!AudioComponentLeft){return;}
	if(!OpenDoorSoundLeft)
	{
		AudioComponentLeft->Play();
		OpenDoorSoundLeft = true;
	}
}

void UOpenDoorLeft::CloseLeftDoor(float DeltaTime)
{
	CurrentYawLeft = FMath::Lerp(CurrentYawLeft, OpenAngleLeft, DeltaTime * DoorOpenSpeedLeft);
	
	FRotator DoorRotationLeft = GetOwner()->GetActorRotation();

	DoorRotationLeft.Yaw = CurrentYawLeft;
	GetOwner()->SetActorRotation(DoorRotationLeft);

	OpenDoorSoundLeft = false;
	if(!AudioComponentLeft){return;}
	if(!CloseDoorSoundLeft)
	{
		AudioComponentLeft->Play();
		CloseDoorSoundLeft = true;
	}
}

float UOpenDoorLeft::TotalMassOfActorsLeft() const
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

// void UOpenDoorLeft::PushButton()
// {
// 	FVector PushButton = GetOwner()->SetActorLocation(1596.359985);

// 	if (TotalMassOfActors())
// 	{
// 		PushButton;
// 	}
// }

