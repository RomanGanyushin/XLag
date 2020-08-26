// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMap.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapWindow.h"
#include "XLagSelectGeometryBuilder.h"
#include "XLagSelectComponent.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagSelectComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXLagSelectComponent();

	/// Selection scene property
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	/// 
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* Selection;

	/// Мателиал должен быть 2Side!
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* SelectionGrid;

	UFUNCTION(BlueprintCallable) void SetFirstWorldPoint(float x, float y);
	UFUNCTION(BlueprintCallable) void SetSecondWorldPoint(float x, float y);

	UPROPERTY(EditAnywhere)
		float WorldPoint1X;

	UPROPERTY(EditAnywhere)
		float WorldPoint1Y;

	UPROPERTY(EditAnywhere)
		float WorldPoint2X;

	UPROPERTY(EditAnywhere)
		float WorldPoint2Y;

	UPROPERTY(EditAnywhere)
		int CellWidth;

	UPROPERTY(EditAnywhere)
		int CellHeight;

	UPROPERTY(EditAnywhere)
		int CellPoistionX;

	UPROPERTY(EditAnywhere)
		int CellPoistionY;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Init(std::shared_ptr<ITerrainMapAccessor> map);
	void Init(std::shared_ptr<ITerrainMapAccessor> map, std::shared_ptr<ITerrainMapAccessor> selection);

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	void GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagSelectGeometryBuilder& geometry);

	void RecalculateSelectView();
	void RecalculateCellWidthAndPosition();
};
