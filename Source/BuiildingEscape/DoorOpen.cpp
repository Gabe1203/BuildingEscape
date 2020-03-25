// Copyright Gabriel Valladares


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
	float InitialYaw = CurrentRotation.Yaw;
	TargetYaw += InitialYaw;
	
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor(DeltaTime);
	}
	
}

void UDoorOpen::OpenDoor(float DeltaTime)
{
	CurrentRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, 45);
	GetOwner()->SetActorRotation(CurrentRotation);
}

