// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagBuildings/XLagBuilding.h"
#include "XLagNPCBuilderman.generated.h"

struct DigMemo
{
	DigMemo(FXLagDynamicTerrainMapItem* cell, float toLevel, bool keepToLevel)
		:targetCell(cell), ToLevel(toLevel), KeepTopLayer(keepToLevel) {}

	FXLagDynamicTerrainMapItem* targetCell;
	float ToLevel;
	bool KeepTopLayer;
};

struct PourMemo
{
	PourMemo(FXLagDynamicTerrainMapItem* cell, float toLevel, TerrainElementEnum element)
		:targetCell(cell), ToLevel(toLevel), Element(element) {}

	FXLagDynamicTerrainMapItem* targetCell;
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Копай клетку.
	virtual void Dig(FXLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer);

	// Насыпай на клетку.
	virtual void Pour(FXLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element);

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
