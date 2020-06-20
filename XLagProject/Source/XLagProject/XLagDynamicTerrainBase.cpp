/// Fill out your copyright notice in the Description page of Project Settings.

#include "XLagDynamicTerrainBase.h"
#include "ProceduralMeshComponent.h"
#include "XLagDynamicTerrain\XLagDynamicTerrainMapFiller.hpp"

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


	XLagDynamicTerrainMapFiller().FillPerlin(Map, 0);
	XLagDynamicTerrainMapFiller().TranslateTo(Map, 200, 1, 2);

	XLagDynamicTerrainLayerGeometry _geometry;

	_geometry.CreateFrom(Map, 0);
	GenerateLayerGeometry(Ground, _geometry);

	_geometry.CreateFrom(Map, 1);
	GenerateLayerGeometry(Sand, _geometry);

	_geometry.CreateTransFrom(Map, 2);
	GenerateLayerGeometry(GroundToSand, _geometry);
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
	
	Ground = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Ground"));
	Ground->SetupAttachment(TerrainScene);

	Sand = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Sand"));
	Sand->SetupAttachment(TerrainScene);

	GroundToSand = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundToSand"));
	GroundToSand->SetupAttachment(TerrainScene);
}

void AXLagDynamicTerrainBase::GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry)
{
	UE_LOG(LogTemp, Warning, TEXT("GenerateLayerGeometry"));
	Component->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
}