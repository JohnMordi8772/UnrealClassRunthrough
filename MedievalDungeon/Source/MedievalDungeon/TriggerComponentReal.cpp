// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponentReal.h"

// Sets default values for this component's properties
UTriggerComponentReal::UTriggerComponentReal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponentReal::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent = GetOwner()->FindComponentByClass<UBoxComponent>();

	if (WallToMove == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("WallToMove not set on Trigger Component"));
		return;
	}

	WallMover = WallToMove->FindComponentByClass<UWallMover>();
	// ...
	
}


// Called every frame
void UTriggerComponentReal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (BoxComponent == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Box Component not set on Trigger Component"));
		return;
	}

	if (WallMover == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("WallMover not set on Trigger Component"));
		return;
	}

	TArray<AActor*> Actors;
	BoxComponent->GetOverlappingActors(Actors);
	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag("OpenDoor1"))
		{
			UE_LOG(LogTemp, Display, TEXT("Unlocking"));
			WallMover->SetMoveTriggered(true);
		}
		//FString ActorName = Actor->GetActorNameOrLabel();
		//UE_LOG(LogTemp, Warning, TEXT("Tick: Overlapped actor's name: %s"), *ActorName)
	}
	// ...
}

