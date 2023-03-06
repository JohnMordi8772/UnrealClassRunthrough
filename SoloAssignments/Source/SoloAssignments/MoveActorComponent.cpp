// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActorComponent.h"

// Sets default values for this component's properties
UMoveActorComponent::UMoveActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();

	//Get the name of the object this component is attatched to
	FString ActorName = GetOwner()->GetActorNameOrLabel();

	//Two ways to get the position of an object
	FString PositionOfObject = GetOwner()->GetActorLocation().ToString();
	
	//Log the name and position of the actor
	UE_LOG(LogTemp, Warning, TEXT("Actor %s is at location %s"), *ActorName, *PositionOfObject);

	//We can log a float or double with %f
	UE_LOG(LogTemp, Warning, TEXT("Actor %s is at x: %f, y: %f"), *ActorName, GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y);

	StartLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveActor(DeltaTime);
	RotateActor(DeltaTime);
}

void UMoveActorComponent::MoveActor(float DeltaTime)
{
	//Move actor forwards
	//Get current location
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	//Add vector to that location
	CurrentLocation = CurrentLocation + MoveVelocity * DeltaTime;
	//set new location
	GetOwner()->SetActorLocation(CurrentLocation);

	//Could write the three lines of code above on one line instead
	//GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + MoveVelocity * DeltaTime);

	//Send actor backwards if end point is reached
	//Check how far the actor has moved
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	//Reverse direction of motion if moved far enough
	if (DistanceMoved >= MoveDistance)
	{
		FVector MoveDirection = MoveVelocity.GetSafeNormal();
		//Set the start location to the end location
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		GetOwner()->SetActorLocation(StartLocation);
		//reverse velocity
		MoveVelocity = -MoveVelocity;
	}
}

void UMoveActorComponent::RotateActor(float DeltaTime)
{
	GetOwner()->AddActorLocalRotation(RotationVelocity * DeltaTime);
}

