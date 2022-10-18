// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DinnerOrDiner_NavGrid.generated.h"

UCLASS()
class DINNERORDINER_UE_API ADinnerOrDiner_NavGrid : public AActor
{
	GENERATED_BODY()

		


		
	
public:	
	// Sets default values for this actor's properties
	ADinnerOrDiner_NavGrid();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FVector GridLocation { 0.0f, 0.0f, 0.1f };
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FVector2D GridSizeWorld = FVector2D(500.0f, 500.0f);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float TileSize = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<USceneComponent> Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UBrushComponent> Brush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug Box | Colors")
		FColor GridBoxColor = { 255, 100, 0 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug Box | Colors")
		FColor BottomLeftColor = { 255, 0, 0 };

	UFUNCTION(BlueprintCallable)
		FVector GridBottomLeft();

	UFUNCTION(BlueprintCallable)
		FVector2D GridTileNumber();

	UFUNCTION(BlueprintCallable)
		void DrawTile();

	UFUNCTION(BlueprintCallable)
		void DrawShape();

	

};
