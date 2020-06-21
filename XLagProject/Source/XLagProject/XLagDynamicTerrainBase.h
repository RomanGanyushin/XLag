/// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "XLagDynamicTerrain/XLagDynamicTerrainMap.h"
#include "XLagDynamicTerrain/XLagDynamicTerrainLayerGeometry.h"
#include "XLagDynamicTerrainBase.generated.h"


UCLASS()
class XLAGPROJECT_API AXLagDynamicTerrainBase : public AActor
{
	GENERATED_BODY()
	
public:	
	/// Sets default values for this actor's properties
	AXLagDynamicTerrainBase();

	/// Terrain scene property
	UPROPERTY(VisibleAnywhere)
		USceneComponent* TerrainScene;

	/// Ground Grass component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* GroundGrass;

	/// Rock Sandstone component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* RockSandstone;

	/// RockBasalt component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* RockBasalt;

	/// Ground Gras To Rock Sandstone component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* GroundGrassToRockSandstone;

	/// Ground Gras To Rock Basalt component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* GroundGrassToRockBasalt;
	
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	XLagDynamicTerrainMap* Map;
	void InitMap();
	

protected:
	void InitializeLayers();
	void GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
