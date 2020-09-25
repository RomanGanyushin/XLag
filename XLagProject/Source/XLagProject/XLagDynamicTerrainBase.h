/// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "XLagDynamicTerrain/XLagDynamicTerrainMapWindow.h"

#include "XLagNPC/XLagCuttableTreeBase.h"
#include "XLagGeometry/Builders/GeometryBuilderAbstract.h"
#include "XLagDynamicTerrainBase.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagDynamicTerrainBase : public AActor
{
	GENERATED_BODY()
	
public:	
	/// Sets default values for this actor's properties
	AXLagDynamicTerrainBase();

// Главные параметры.
public:
	// Масштаб.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Main Params")
	float Scale = 100;

	// Размер локации по оси X.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Main Params")
	int FullMapSizeX = 100;

	// Размер локации по оси Y.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Main Params")
	int FullMapSizeY = 100;

	// Размер окна локации по оси X.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Main Params")
	int WindowMapSizeX = 100;

	// Размер окна локации по оси Y.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Main Params")
	int WindowMapSizeY = 100;

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Generator")
	float 	Amplitude = 5000.f;

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Generator")
	float 	Octaves = 5;

	// Радиус нулевой локации.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zero Location")
	float ZeroLocationRadius = 5;

	// Высота нулевой локации.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zero Location")
	float ZeroLocationHeight = 0;


// Ресурсы.
public:
	// Плотность леса. Количество квадратных метров на дерево.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "On Surface Resource Settings")
	int AreaPerTree = 16;


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

	/// Coil component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* Coal;

	/// Ground Gras To Rock Sandstone component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* GroundGrassToRockSandstone;

	/// Ground Gras To Rock Basalt component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* GroundGrassToRockBasalt;

	/// Ground Gras To Coil component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* GroundGrassToCoal;

	/// Ground Gras To Rock Basalt component
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* RockSandstoneToRockBasalt;

	/// 
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* ColorizeMapper;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	std::shared_ptr<ITerrainMapAccessor> Map;
	std::shared_ptr<ITerrainMapAccessor> CurrentMap;

	void InitMap();
	void InitGeometry();
	void AddGreader();

	UStaticMeshComponent *Grader = nullptr;
	TArray<AXLagCuttableTreeBase*> Trees;

protected:
	void InitializeLayers();
	void GenerateLayerGeometry(UProceduralMeshComponent* Component, GeometryBuilderAbstract* geometry);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
