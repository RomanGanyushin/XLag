/// Fill out your copyright notice in the Description page of Project Settings.

#include "XLagDynamicTerrainBase.h"
#include "ProceduralMeshComponent.h"
#include "XLagDynamicTerrain\XLagDynamicTerrainMapFiller.hpp"

#include "XLagDynamicTerrain\MapBuilder\TerrainElementEnum.h"
#include "XLagDynamicTerrain\MapBuilder\TerrainMapEditEditor.h"
#include "XLagDynamicTerrain\MapBuilder\Components\PerlinFillerMapEditComponent.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTranformComponent.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransofmHigherCondition.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransofmBelowCondition.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransformNeighbourCondition.h"

// Sets default values
AXLagDynamicTerrainBase::AXLagDynamicTerrainBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TerrainScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = TerrainScene;
	InitializeLayers();

	InitMap();

	UE_LOG(LogTemp, Warning, TEXT("AXLagDynamicTerrainBase construct 056"));
}

void AXLagDynamicTerrainBase::PostActorCreated()
{
	InitMap();
	Super::PostActorCreated();
}

void AXLagDynamicTerrainBase::PostLoad()
{
	InitMap();
	Super::PostLoad();
}

void AXLagDynamicTerrainBase::InitMap()
{
	
	if (Map != nullptr)
	{
		delete Map;
	}

	Map = new XLagDynamicTerrainMap(100, 100);
	Map->Initialize();



	TerrainMapEditEditor editor(Map);
	PerlinFillerMapEditComponent perlinComp(TerrainElementEnum::GraundGrass);
	editor.FillByXY(&perlinComp);

	TerrainElementTranformComponent makeRock(
		TerrainElementTransofmHigherCondition(300),
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::RockBasalt);
	editor.FillByXY(&makeRock);

	TerrainElementTranformComponent makeHollow(
		TerrainElementTransofmBelowCondition(-100),
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::RockSandstone);
	editor.FillByXY(&makeHollow);

	TerrainElementTranformComponent makeTransitionGrassToBasalt
	(
		TerrainElementTransformNeighbourCondition(TerrainElementEnum::RockBasalt),
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::GrondGrassToRockBasaltTrans
	);
	editor.FillByXY(&makeTransitionGrassToBasalt);

	TerrainElementTranformComponent makeTransitionGrassToSandstone
	(
		TerrainElementTransformNeighbourCondition(TerrainElementEnum::RockSandstone),
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::GroundGrassToRockSandstoneTrans
	);
	editor.FillByXY(&makeTransitionGrassToSandstone);


	XLagDynamicTerrainLayerGeometry _geometry;

	_geometry.CreateFrom(Map, TerrainElementEnum::GraundGrass);
	GenerateLayerGeometry(GroundGrass, _geometry);

	_geometry.CreateFrom(Map, TerrainElementEnum::RockSandstone);
	GenerateLayerGeometry(RockSandstone, _geometry);

	_geometry.CreateFrom(Map, TerrainElementEnum::RockBasalt);
	GenerateLayerGeometry(RockBasalt, _geometry);

	_geometry.CreateTransFrom(Map, TerrainElementEnum::GroundGrassToRockSandstoneTrans);
	GenerateLayerGeometry(GroundGrassToRockSandstone, _geometry);

	_geometry.CreateTransFrom(Map, TerrainElementEnum::GrondGrassToRockBasaltTrans);
	GenerateLayerGeometry(GroundGrassToRockBasalt, _geometry);
}

// Called when the game starts or when spawned
void AXLagDynamicTerrainBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXLagDynamicTerrainBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLagDynamicTerrainBase::InitializeLayers()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize layers"));
	
	GroundGrass = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrass"));
	GroundGrass->SetupAttachment(TerrainScene);

	RockSandstone = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RockSandstone"));
	RockSandstone->SetupAttachment(TerrainScene);

	RockBasalt = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RockBasalt"));
	RockBasalt->SetupAttachment(TerrainScene);


	GroundGrassToRockSandstone = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrassToRockSandstone"));
	GroundGrassToRockSandstone->SetupAttachment(TerrainScene);

	GroundGrassToRockBasalt = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrassToRockBasalt"));
	GroundGrassToRockBasalt->SetupAttachment(TerrainScene);
}

void AXLagDynamicTerrainBase::GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry)
{
	UE_LOG(LogTemp, Warning, TEXT("GenerateLayerGeometry"));
	Component->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
}