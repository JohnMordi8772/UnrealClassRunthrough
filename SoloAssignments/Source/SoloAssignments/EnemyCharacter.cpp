// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Fetch the character currently being controlled by the player
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	bCanSeePlayer = LookAtActor(PlayerCharacter, DeltaTime);

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnemyCharacter::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	bPreviousCanSeePlayer = bCanSeePlayer;
}

bool AEnemyCharacter::LookAtActor(AActor* TargetActor, float DeltaTime)
{
	if (TargetActor == nullptr) return false;

	if (CanSeeActor(TargetActor))
	{
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		// Calculate the necessary rotation for the start point to face the end point
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		// Set the enemy's rotation to that rotation
		SetActorRotation(LookAtRotation);

		return true;
	}

	return false;
}

bool AEnemyCharacter::CanSeeActor(const AActor* const TargetActor) const
{
	if (TargetActor == nullptr) return false;

	//Store the results of the line trace
	FHitResult Hit;

	// Where the line trace starts and ends
	FVector Start = GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	// The trace channel we want to compare against
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;

	FCollisionQueryParams QueryParams;
	//Ignore the actor that's executing this line trace
	QueryParams.AddIgnoredActor(this);
	//And the target we're checking for
	QueryParams.AddIgnoredActor(TargetActor);

	//Execute the line trace
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	// Set color green if blocked or red if not blocked
	FColor LineColor = (Hit.bBlockingHit) ? FColor::Green : FColor::Red;

	//Show the line trace inside the game
	DrawDebugLine(GetWorld(), Start, End, LineColor);

	return !Hit.bBlockingHit;
}

void AEnemyCharacter::ThrowDodgeball()
{
	if (Dodgeball == nullptr)
		return;

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	GetWorld()->SpawnActor<ADodgeballProjectile>(Dodgeball, SpawnLocation, GetActorRotation());
}

// Called to bind functionality to input
//void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

