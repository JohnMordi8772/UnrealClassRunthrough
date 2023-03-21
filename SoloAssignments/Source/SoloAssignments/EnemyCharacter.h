// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class SOLOASSIGNMENTS_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	float Count;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball)
	TSubclassOf<class ADodgeballProjectile> Dodgeball;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bCanSeePlayer = false;
	bool bPreviousCanSeePlayer = false;

	FTimerHandle ThrowTimerHandle;
	float ThrowingInterval = 2.f;
	float ThrowingDelay = 0.5f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Change the rotation of the character to the face the given actor
	bool LookAtActor(AActor* TargetActor, float DeltaTime);

	//Can we see the given actor
	bool CanSeeActor(const AActor* const TargetActor) const;

	//Throw dodgeball
	void ThrowDodgeball();

};
