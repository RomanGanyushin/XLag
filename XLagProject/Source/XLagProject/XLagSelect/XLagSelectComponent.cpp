// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagSelectComponent.h"


// Sets default values
AXLagSelectComponent::AXLagSelectComponent()
	: WorldPoint1X(5000), WorldPoint1Y(5000), WorldPoint2X(5500), WorldPoint2Y(5500)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Selection = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Selection"));
	Selection->SetupAttachment(Root);

	SelectionGrid = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("SelectionGrid"));
	SelectionGrid->SetupAttachment(Root);

	XLagSelectGeometryBuilder _geometry;
	_geometry.CreateDefault();
	GenerateLayerGeometry(Selection, _geometry);
	GenerateLayerGeometry(SelectionGrid, _geometry);
}

void AXLagSelectComponent::Init(std::shared_ptr<ITerrainMapAccessor> map)
{
	Map = map;

	RecalculateCellWidthAndPosition();
	RecalculateSelectView();
}

void AXLagSelectComponent::Init(std::shared_ptr<ITerrainMapAccessor> map, std::shared_ptr<ITerrainMapAccessor> selection)
{
	WorldPoint1X = selection->GetWorldPosition(0, 0, LeftBottomPosition).X;
	WorldPoint1Y = selection->GetWorldPosition(0, 0, LeftBottomPosition).Y;
	WorldPoint2X = selection->GetWorldPosition(selection->SizeX() - 1, selection->SizeY() - 1, RightBottomPosition).X;
	WorldPoint2Y = selection->GetWorldPosition(selection->SizeX() - 1, selection->SizeY() - 1, RightBottomPosition).Y;

	Init(map);
}

// Called when the game starts or when spawned
void AXLagSelectComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXLagSelectComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLagSelectComponent::SetFirstWorldPoint(float x, float y)
{
	WorldPoint1X = x;
	WorldPoint1Y = y;

	RecalculateCellWidthAndPosition();
	RecalculateSelectView();
}

void AXLagSelectComponent::SetSecondWorldPoint(float x, float y)
{
	WorldPoint2X = x;
	WorldPoint2Y = y;

	RecalculateCellWidthAndPosition();
	RecalculateSelectView();
}

void AXLagSelectComponent::RecalculateCellWidthAndPosition()
{
	if (Map == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AXLagSelectComponent::RecalculatreSelectView. Map == nullptr"));
	}

	int index_x1 = WorldPoint1X / 100.0;
	int index_y1 = WorldPoint1Y / 100.0;

	int index_x2 = WorldPoint2X / 100.0;
	int index_y2 = WorldPoint2Y / 100.0;

	CellPoistionX = std::min(index_x1, index_x2);
	CellPoistionY = std::min(index_y1, index_y2);

	CellWidth = std::abs(index_x1 - index_x2);
	CellHeight = std::abs(index_y1 - index_y2);
}

void AXLagSelectComponent::RecalculateSelectView()
{
	if (CellWidth == 0 || CellHeight == 0)
		return;

	auto select = Map->CreateWindow(CellPoistionX, CellPoistionY, CellWidth, CellHeight);

	XLagSelectGeometryBuilder _geometry;
	_geometry.CreateSelection(select);
	GenerateLayerGeometry(Selection, _geometry);

	_geometry.CreateGrid(select);
	GenerateLayerGeometry(SelectionGrid, _geometry);
}

void AXLagSelectComponent::GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagSelectGeometryBuilder& geometry)
{
	UE_LOG(LogTemp, Warning, TEXT("XLagSelectComponent::GenerateLayerGeometry"));
	Component->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
}


