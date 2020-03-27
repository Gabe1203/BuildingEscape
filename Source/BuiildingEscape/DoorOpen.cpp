// Copyright Gabriel Valladares

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DoorOpen.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	
	CurrentRotation = GetOwner()->GetActorRotation();
	InitialYaw = CurrentRotation.Yaw;
	TargetYaw += InitialYaw;

	if(!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("Has OpenDoor but no pressure plae: %s"), *GetOwner()->GetName())
	}

	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//First PressurePlate check prevents against null pointer on pressure platewd
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}else
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (CurrentTime - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}

	
	
}

void UDoorOpen::OpenDoor(float DeltaTime)
{
	CurrentRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, 45);
	GetOwner()->SetActorRotation(CurrentRotation);
}

void UDoorOpen::CloseDoor(float DeltaTime)
{
	CurrentRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, InitialYaw, DeltaTime, 120);
	GetOwner()->SetActorRotation(CurrentRotation);
}

