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

	Map = new XLagDynamicTerrainMap(100, 100);
	Map->Initialize();
	
	XLagDynamicTerrainMapFiller().FillAsRombe(Map, 0);
	XLagDynamicTerrainMapFiller().FillAsRombeHole(Map, 1);
	//XLagDynamicTerrainMapFiller().FillAsHoleOuterQuad(Map, 0, -100, 0);
	//XLagDynamicTerrainMapFiller().FillAsHoleInnerQuad(Map, -100, 1);

	XLagDynamicTerrainLayerGeometry _geometry;
	
	_geometry.CreateFrom(Map, 0);
	GenerateLayerGeometry(Ground, _geometry);

	_geometry.CreateFrom(Map, 1);
	GenerateLayerGeometry(Sand, _geometry);

	UE_LOG(LogTemp, Warning, TEXT("AXLagDynamicTerrainBase construct"));
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
}

void AXLagDynamicTerrainBase::GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry)
{
	UE_LOG(LogTemp, Warning, TEXT("GenerateLayerGeometry"));
	Component->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
}