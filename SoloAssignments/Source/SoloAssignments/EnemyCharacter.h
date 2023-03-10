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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Dodgeball;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Change the rotation of the character to the face the given actor
	void LookAtActor(AActor* TargetActor, float DeltaTime);

	//Can we see the given actor
	bool CanSeeActor(const AActor* const TargetActor) const;

	//Throw dodgeball
	void ThrowDodgeball();

};
