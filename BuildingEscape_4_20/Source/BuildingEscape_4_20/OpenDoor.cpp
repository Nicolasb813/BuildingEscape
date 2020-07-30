// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DefaultPawn.h"
#include "Components/PrimitiveComponent.h"
#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//
	if (!PressurePlate)
	{
		return;
	}
	Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PressurePlate)
	{
		return;
	}
	if (PressurePlate && GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{

	float TotalMass = 0.f;
	TArray<AActor *> OverlapingActors;
	if (!PressurePlate)
	{
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OUT OverlapingActors);
	
	for (const auto *Actor : OverlapingActors)
	{

		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT(" %s on pressure plate"), *(Actor->GetName()));				
	}

	return TotalMass;
}
