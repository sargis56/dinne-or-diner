// Fill out your copyright notice in the Description page of Project Settings.


#include "DinnerOrDiner_NavGrid.h"
#include "Components/SceneComponent.h"
#include "Components/BillBoardComponent.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BrushComponent.h"


// Sets default values
ADinnerOrDiner_NavGrid::ADinnerOrDiner_NavGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlushPersistentDebugLines(GetWorld());
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	
	RootComponent = Scene;

	GridLocation.Set(Scene->GetComponentLocation().X, Scene->GetComponentLocation().Y, Scene->GetComponentLocation().Z);

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));
	Billboard->SetHiddenInSceneCapture(false);
	Billboard->SetupAttachment(RootComponent);

	Brush = CreateDefaultSubobject<UBrushComponent>(TEXT("BrushComponent"));
	Brush->SetupAttachment(RootComponent);
	

	
	
}



// Called when the game starts or when spawned
void ADinnerOrDiner_NavGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADinnerOrDiner_NavGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

FVector ADinnerOrDiner_NavGrid::GridBottomLeft()
{
	FVector gridBottomLeft;
	FVector temp;

	gridBottomLeft = GridLocation - (Scene->GetRightVector() * GridSizeWorld.X);
	temp = Scene->GetForwardVector() * GridSizeWorld.Y;

	gridBottomLeft -= temp;

	return gridBottomLeft;
}

FVector2D ADinnerOrDiner_NavGrid::GridTileNumber()
{
	FVector2D TileNumber;
	FVector2D temp;

	temp = GridSizeWorld / TileSize;
	temp = temp.RoundToVector();
	

	return TileNumber = temp;
}

void ADinnerOrDiner_NavGrid::DrawTile()
{
	FVector TilePosition;
	for (int x = 0; x < GridTileNumber().X; ++x)
	{
		for (int y = 0; y < GridTileNumber().Y; ++y)
		{
			TilePosition = GridBottomLeft() + ( Scene->GetRightVector() * ( (x * (TileSize * 2.0f)) + TileSize ) + ( Scene->GetForwardVector() * ( (y * ( TileSize * 2.0f ) + TileSize) )) );
			DrawDebugSolidPlane(GetWorld(), FPlane4d(0.0, 0.0, 1.0, TilePosition.Z), TilePosition, TileSize - 5.0f, FColor(0.0, 100.0, 0.0), false, 5.0f);
			
		}
	}
}

void ADinnerOrDiner_NavGrid::DrawShape()
{

	DrawDebugBox(GetWorld(), FVector(GridLocation.X, GridLocation.Y, GridLocation.Z), FVector(GridSizeWorld.Y, GridSizeWorld.X, 5), GridBoxColor, false, 5.0f, (uint8)0U, 5.0f);// outer square
	DrawDebugBox(GetWorld(), GridBottomLeft(), FVector(20, 20, 20), BottomLeftColor, false, 5.0f, (uint8)0U, 5.0f);

}

