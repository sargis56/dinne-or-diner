// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "DinnerOrDiner_UECharacter.h"
#include "AI_Bear_char.generated.h"

/*IN THE BLUEPRINT, AI CONTROLLER CLASS IS SET TO "None"*/

UCLASS()
class DINNERORDINER_UE_API AAI_Bear_char : public ACharacter
{
	GENERATED_BODY()

public:

	

	// Sets default values for this character's properties
	AAI_Bear_char();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SeekActor(float time, AActor* targetActor_);
	void SeekPosition(float time);

	void StopSeeking();
	void PerformRaycast();

	void RotateTowards(FVector ActorLocation_);

	// other states the AI may execute
	/*
	rtrn_type AIAttackPawn(AActor* Pawn_); this can also be used for other actors since APawn inherits from AActor
	rtrn_type AIAttackActor(AActor* Actor_); the ^^functions^^ take the same type, but for simplicity you could have two different functions so it doesn't get clusterd into one
	rtrn_type AIAttackCharacter(ACaracter* Pawn_); probably not needed since ACharacter inherits from AActor
	rtrn_type AIAttack();
	rtrn_type AIStopAttack(); this may or may not be needed, depends on if we use something like states
	*/

	bool isColliding = false;
	bool isSeeking = false;
	FHitResult* CollidedActor;

	UPawnMovementComponent* AI_MovementComponent;
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UPROPERTY(EditDefaultsOnly, Category = "AI | Senses")
		float AI_SeeRadius = 1500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI | Senses")
		float AI_PawnSpotRadius = 500.0f;

	UPROPERTY(BlueprintReadOnly, Category = "AI | Extras")
		FVector AI_position;

	UPROPERTY(BlueprintReadOnly, Category = "AI | Extras")
		FVector AI_velocity;

	UPROPERTY(BlueprintReadOnly, Category = "AI | Extras")
		float AI_speed;										// this can be used to set a vector...maybe

	UPROPERTY(EditAnywhere, Category = "Debug")
		bool debugArrow = false;

private:
	
	

	UPROPERTY()
		ADinnerOrDiner_UECharacter* c_player;									// c_ means character



};
