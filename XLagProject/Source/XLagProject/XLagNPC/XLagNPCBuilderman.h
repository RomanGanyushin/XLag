// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagBuildings/XLagBuilding.h"
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
	// Копай клетку.
	virtual void Dig(XLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer);

	// Насыпай на клетку.
	virtual void Pour(XLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element);

	// Строй здание.
	virtual void Build(AXLagBuilding* building);


	// Отменяет выполняемую команду.
	void Cancel();


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Builderman Working")
		bool  IsDiging = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Builderman Working")
		bool  IsPouring = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Builderman Working")
		bool  IsBuilding = false;

	virtual void OfferAccept(UXLagTaskBase* task) override;

private:
	std::shared_ptr<DigMemo> digMemo;
	std::shared_ptr<PourMemo> pourMemo;

protected:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Builder; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }
};
