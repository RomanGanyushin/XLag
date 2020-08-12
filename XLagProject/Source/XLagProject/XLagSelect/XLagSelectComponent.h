// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMap.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapWindow.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainLayerGeometry.h"
#include "XLagSelectComponent.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagSelectComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXLagSelectComponent();

	/// Terrain scene property
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	/// 
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* Selection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Init(std::shared_ptr<ITerrainMapAccessor> map);

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	std::shared_ptr<ITerrainMapAccessor> CurrentMap;
	void GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry);
};
