// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "XLagNPCBuilderman.generated.h"

struct DigMemo
{
	DigMemo(XLagDynamicTerrainMapItem* cell, float toLevel, bool keepToLevel)
		:targetCell(cell), ToLevel(toLevel), KeepTopLayer(keepToLevel) {}

	XLagDynamicTerrainMapItem* targetCell;
	float ToLevel;
	bool KeepTopLayer;
};

struct PourMemo
{
	PourMemo(XLagDynamicTerrainMapItem* cell, float toLevel, TerrainElementEnum element)
		:targetCell(cell), ToLevel(toLevel), Element(element) {}

	XLagDynamicTerrainMapItem* targetCell;
	float ToLevel;
	TerrainElementEnum Element;
};

/**
 * 
 */
UCLASS()
class XLAGPROJECT_API AXLagNPCBuilderman : public AXLagNPCBase
{
	GENERATED_BODY()

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// ����� ������.
	virtual void Dig(XLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer);

	// ������� �� ������.
	virtual void Pour(XLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element);


	// �������� ����������� �������.
	void Cancel();


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Builderman Working")
		bool  IsDiging = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Builderman Working")
		bool  IsPouring = false;

private:
	std::shared_ptr<DigMemo> digMemo;
	std::shared_ptr<PourMemo> pourMemo;
};
