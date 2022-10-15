// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Bear_char.h"
#include "Components/CapsuleComponent.h"
#include "Bear_AIController.h"
#include <Kismet/GameplayStatics.h>
#include "Engine.h"
#include <GameFramework/MovementComponent.h>
#include "Math/Vector.h"


// Sets default values
AAI_Bear_char::AAI_Bear_char()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AAI_Bear_char::BeginPlay()
{
	Super::BeginPlay();

	//init senses and other vars
	AI_SeeRadius =			1500.0f;
	AI_PawnSpotRadius =		500.0f;
	AI_speed =				350.0f;
	AI_velocity =			FVector(0.0f, 0.0f, 0.0f);
	AI_position =			GetActorLocation();
	c_player =				Cast<ADinnerOrDiner_UECharacter>(
								 UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));// get ref to the player

	CollidedActor = new FHitResult();
	
	
	
}

// Called every frame
void AAI_Bear_char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformRaycast();

	FVector Vecdistance = GetActorLocation() - c_player->GetActorLocation();
	float distance = Vecdistance.Size();
	if (distance <= AI_PawnSpotRadius)
	{
		//isSeeking = true;
		if (isColliding && !isSeeking)
		{
			SeekPosition(DeltaTime);
			isSeeking = false;
		}

		if(isSeeking)
		{
			SeekActor(DeltaTime, c_player);
		}
		
		

		GEngine->AddOnScreenDebugMessage(-1, 0.017f, FColor::Green, TEXT("Chasing Player"));
	}
	else if (distance <= AI_SeeRadius)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.017f, FColor::Yellow, TEXT("I think I see Something?"));
	}
	else if (distance > AI_PawnSpotRadius)
	{
		StopSeeking();
		GEngine->AddOnScreenDebugMessage(-1, 0.017f, FColor::Red, TEXT("Waiting For EIS"));
	}

	

	
	
	
}

// Called to bind functionality to input
void AAI_Bear_char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Bear_char::SeekPosition(float time)
{
	//Get normal from where Raycast touches actor, get distance along normal, make that point the new target for the seek
	//if the actor is phasing through obstacle, might need to adjust raycast length
	FVector normal = CollidedActor->Normal;
	FVector location = CollidedActor->Location;
	FVector s_trace = CollidedActor->TraceStart;
	FVector e_trace = CollidedActor->TraceEnd;
	FVector LineEnd;

	FVector UnitVector = s_trace - e_trace;//direction
	UnitVector.Normalize();

	FVector mir_normal = normal.MirrorByVector(UnitVector);// get the mirrored vector from the normal
	mir_normal *= 96.0f;// length of arrow

	LineEnd = location + mir_normal;// calculate the end my adding the start of the line which is the hit location + the length of the arrow


	if(debugArrow)// is editable anywhere, a bool in the details panel under "Debug"
		DrawDebugDirectionalArrow(GetWorld(), location, LineEnd, 30.0f, FColor(0, 50, 100), false, 5.0f, (uint8)0U, 10.0f);

	RotateTowards(location + (mir_normal * 46.0f));
	//AddActorLocalRotation(FQuat(FVector3d(0, 0, 1), double(25)));

	AI_velocity = ( location + (mir_normal * (GetCapsuleComponent()->GetScaledCapsuleRadius() * 0.75f)) ) - GetActorLocation();// direction
	AI_velocity.Normalize();// normalize it to prevent max clipping
	AI_velocity *= AI_speed;// apply the speed to it so the AI moves relative to the set speed
	AI_velocity.Z = 0;
	AI_position += AI_velocity * time;// update the AIs position with the velocity and time

	SetActorLocation(AI_position);
}

void AAI_Bear_char::SeekActor(float time, AActor* targetActor_)
{
		
	RotateTowards(targetActor_->GetActorLocation());

	// AI movement
	AI_velocity = targetActor_->GetActorLocation() - GetActorLocation();// direction
	AI_velocity.Normalize();// normalize it to prevent max clipping
	AI_velocity *= AI_speed;// apply the speed to it so the AI moves relative to the set speed
	AI_position += AI_velocity * time;// update the AIs position with the velocity and time

	SetActorLocation(AI_position);// set the current position to the new position


}

void AAI_Bear_char::StopSeeking()
{
	
	isSeeking = false;
	AI_velocity = FVector();
}

void AAI_Bear_char::PerformRaycast()
{
	
	FVector StartTrace = GetMesh()->GetComponentLocation() + FVector(0.0f, 0.0f, 100.0f);// 100.0 is the offset in the Z because unreal uses the Z axis as up/down instead of Y... why..?
	FVector ForwardVector = GetCapsuleComponent()->GetForwardVector();// length
	FVector EndTrace = ((ForwardVector * (GetCapsuleComponent()->GetScaledCapsuleRadius() * 0.75f)) + StartTrace);// since we add the StartTrace to the EndTrace we don't need to add an offset unless you want the line to be on angle
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	

	if (GetWorld()->LineTraceSingleByChannel(*CollidedActor, StartTrace, EndTrace, ECC_Visibility, *TraceParams))//ECC_Visibility
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 5.0f);
	
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("You hit: %s"), *CollidedActor->GetActor()->GetName()));
		
		//get rid of isColliding bool? maybe I still need it
		isColliding = true;
		isSeeking = false;
		
	}
	else
	{
		isColliding = false;
		isSeeking = true;
	}

		
	EndTrace = ((ForwardVector * (GetCapsuleComponent()->GetScaledCapsuleRadius() * 0.75f)) + (StartTrace + FVector(10.0f, 10.0, 0.0f)));
	
	//right
	if (GetWorld()->LineTraceSingleByChannel(*CollidedActor, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0), false, 5.0f);
		isColliding = true;
		isSeeking = false;
	}
	else
	{
		isColliding = false;
		isSeeking = true;
	}

	EndTrace = ((ForwardVector * (GetCapsuleComponent()->GetScaledCapsuleRadius() * 0.75f)) + (StartTrace + FVector(-10.0f, -10.0, 0.0f)));
	//left
	if (GetWorld()->LineTraceSingleByChannel(*CollidedActor, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0), false, 5.0f);
		isColliding = true;
		isSeeking = false;
	}
	else
	{
		isColliding = false;
		isSeeking = true;
	}
	

	//ground line trace
	/*EndTrace = ((ForwardVector * (GetCapsuleComponent()->GetScaledCapsuleRadius() * 2.0f)) + StartTrace) - FVector(0.0f, 0.0f, 260.0f);
	if (GetWorld()->LineTraceSingleByChannel(*CollidedActor, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 5.0f);
		
	}*/

}

void AAI_Bear_char::RotateTowards(FVector ActorLocation_)
{
	// AI transform rotation
	FVector LocA = GetActorLocation();
	FVector LocB = ActorLocation_;

	FVector NewLocation = (LocA + LocB) * 0.5f;
	FRotator NewRotation = (LocB - LocA).Rotation();

	FTransform NewTransform{ NewRotation, NewLocation };

	SetActorTransform(NewTransform);
}

UPawnMovementComponent* AAI_Bear_char::GetMovementComponent() const
{
	return AI_MovementComponent;
}






