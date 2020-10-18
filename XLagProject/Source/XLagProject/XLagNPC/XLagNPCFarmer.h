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

	// ������� ������.
	virtual bool Plough(XLagDynamicTerrainMapItem& cell, float DeltaTime);

	// ����� ������.
	virtual bool Sow(XLagDynamicTerrainMapItem& cell, const FXLagCropDescription& crop, float DeltaTime);


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsPloughing = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsSowing = false;

private:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Farmer; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }

private:
	bool ValidateCell(XLagDynamicTerrainMapItem& cell);

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
