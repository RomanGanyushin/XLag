#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagCrops/XLagCropManager.h"
#include "XLagNPCFarmer.generated.h"

/**
 *
 */
UCLASS()
class XLAGPROJECT_API AXLagNPCFarmer : public AXLagNPCBase
{
	GENERATED_BODY()

public:
	virtual void OfferAccept(UXLagTaskBase* task) override;

	// Пазхать клетку.
	virtual bool Plough(XLagDynamicTerrainMapItem& cell, float DeltaTime);

	// Сеять клетку.
	virtual bool Sow(XLagDynamicTerrainMapItem& cell, const FXLagCropDescription& crop, float DeltaTime);

	// Выращивать (ухаживать, поливать)
	virtual bool Grow(XLagDynamicTerrainMapItem& cell, float DeltaTime);

	// Собирать урожай.
	virtual bool TakeCrop(XLagDynamicTerrainMapItem& cell, float DeltaTime);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsPloughing = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsSowing = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsGrowing = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsCropTaking = false;
	
	// Объем собранного урожая.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		float  CollectedCropQuantity = 0.0f;

private:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Farmer; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }

private:
	bool ValidateForSowCell(XLagDynamicTerrainMapItem& cell);
	bool ValidateForGrowCell(XLagDynamicTerrainMapItem& cell);
	bool ValidateForTakeCropCell(XLagDynamicTerrainMapItem& cell);

//private:
//	inline AXLagMineralManager* GetMineralManager()
//	{
//		static AXLagMineralManager* mineralManager = nullptr;
//		if (mineralManager == nullptr)
//		{
//			mineralManager = AXLagMineralManager::GetMineralManager();
//		}
//
//		return mineralManager;
//	}
};
