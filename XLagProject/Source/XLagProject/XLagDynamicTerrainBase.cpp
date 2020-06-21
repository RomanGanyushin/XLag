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

#include "Kismet/GameplayStatics.h"

// Sets default values
AXLagDynamicTerrainBase::AXLagDynamicTerrainBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TerrainScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = TerrainScene;
	InitializeLayers();

	InitMap();
	InitGeometry();

	UE_LOG(LogTemp, Warning, TEXT("AXLagDynamicTerrainBase construct 056"));
}

void AXLagDynamicTerrainBase::PostActorCreated()
{
	InitMap();
	InitGeometry();
	Super::PostActorCreated();
}

void AXLagDynamicTerrainBase::PostLoad()
{
	InitMap();
	InitGeometry();
	Super::PostLoad();
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

	APawn *avatar = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (avatar == nullptr)
		return;

	FVector toPlayer = avatar->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), toPlayer.X, toPlayer.Y, toPlayer.Z);
	auto mapCoordsX = (int)toPlayer.X / 100 + 50;
	auto mapCoordsY = (int)toPlayer.Y / 100 + 50;

	auto& level00 = Map->Point(mapCoordsX, mapCoordsY).Stack.back().Level;
	auto& level01 = Map->Point(mapCoordsX, mapCoordsY+1).Stack.back().Level;
	auto& level11 = Map->Point(mapCoordsX+1, mapCoordsY+1).Stack.back().Level;
	auto& level10 = Map->Point(mapCoordsX+1, mapCoordsY).Stack.back().Level;
	
	auto lmin = std::min(std::min(level00, level01), std::min(level11, level10));
	auto lmax = std::max(std::max(level00, level01), std::max(level11, level10));
	auto ldelta = lmax - lmin;
	auto lcut = std::min(ldelta, 1.f);
	
	level00 = std::max(level00 - lcut, lmin) - 1;
	level01 = std::max(level01 - lcut, lmin) - 1;
	level11 = std::max(level11 - lcut, lmin) - 1;
	level10 = std::max(level10 - lcut, lmin) - 1;

	UE_LOG(LogTemp, Warning, TEXT("Level %f"), level00);
	InitGeometry();
	
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
}

void AXLagDynamicTerrainBase::InitGeometry()
{

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

void AXLagDynamicTerrainBase::GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry)
{
	UE_LOG(LogTemp, Warning, TEXT("GenerateLayerGeometry"));
	Component->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
}