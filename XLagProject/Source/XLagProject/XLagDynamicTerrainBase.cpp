// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagDynamicTerrainBase.h"

// Sets default values
AXLagDynamicTerrainBase::AXLagDynamicTerrainBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TerrainScene = CreateDefaultSubobject<USceneComponent>(TEXT("Terrain scene"));
	RootComponent = TerrainScene;
	
	auto layer = new CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	layer->SetupAttachment(TerrainScene);
	TerrainLayers.Add(layer);

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

