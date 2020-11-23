#pragma once
#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagBuildings/XLagBuilding.h"
#include "XLagNPCBuilderman.generated.h"

/**
 * 
 */
UCLASS()
class XLAGPROJECT_API AXLagNPCBuilderman : public AXLagNPCBase
{
	GENERATED_BODY()
public:
	// Копай клетку.
	virtual bool Dig(FXLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer);

	// Насыпай на клетку.
	virtual bool Pour(FXLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element);

	// Строй здание.
	virtual void Build(AXLagBuilding* building);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Builderman Working")
		bool  IsDiging = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Builderman Working")
		bool  IsPouring = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Builderman Working")
		bool  IsBuilding = false;

	virtual void OfferAccept(UXLagTaskBase* task) override;

protected:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Builder; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }
};
