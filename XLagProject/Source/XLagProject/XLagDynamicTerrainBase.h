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

	/// Ground component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* Ground;

	/// Sand component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* Sand;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	XLagDynamicTerrainMap* Map;
	

protected:
	void InitializeLayers();
	void GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
