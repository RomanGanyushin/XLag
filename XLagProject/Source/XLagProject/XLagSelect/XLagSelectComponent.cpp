// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagSelectComponent.h"

// Sets default values
AXLagSelectComponent::AXLagSelectComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Selection = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Selection"));
	Selection->SetupAttachment(Root);

	XLagDynamicTerrainLayerGeometry _geometry;
	_geometry.CreateDefault();
	GenerateLayerGeometry(Selection, _geometry);
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

void AXLagSelectComponent::Init(std::shared_ptr<ITerrainMapAccessor> map)
{
	Map = map;

	XLagDynamicTerrainLayerGeometry _geometry;
	_geometry.CreateSelection(Map);
	GenerateLayerGeometry(Selection, _geometry);
}

void AXLagSelectComponent::GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry)
{
	UE_LOG(LogTemp, Warning, TEXT("GenerateLayerGeometry"));
	Component->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
}

