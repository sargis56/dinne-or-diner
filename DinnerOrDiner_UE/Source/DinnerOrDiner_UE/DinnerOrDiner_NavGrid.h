// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DinnerOrDiner_NavGrid.generated.h"

UCLASS()
class DINNERORDINER_UE_API ADinnerOrDiner_NavGrid : public AActor
{
	GENERATED_BODY()

		

	UPROPERTY(EditDefaultsOnly, Category = "Debug Box | Colors")
		FColor GridBoxColor = {255, 100, 0};

	UPROPERTY(EditDefaultsOnly, Category = "Debug Box | Colors")
		FColor BottomLeftColor = { 255, 100, 0 };
		
	
public:	
	// Sets default values for this actor's properties
	ADinnerOrDiner_NavGrid();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		FVector GridLocation;
	
	UPROPERTY()
		FVector2D GridSizeWorld;

	UPROPERTY()
		float TileSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<USceneComponent> Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<AActor> Actor;

	UFUNCTION(BlueprintCallable)
		FVector GridBottomLeft();

	UFUNCTION(BlueprintCallable)
		FVector2D GridTileNumber();

	UFUNCTION(BlueprintCallable)
		void DrawTile();

};
