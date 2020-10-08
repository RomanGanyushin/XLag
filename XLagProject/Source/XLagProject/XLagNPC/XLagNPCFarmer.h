#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagMinerals/XLagMineralManager.h"
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

	// Ищи минерал в клетке.
	virtual bool Cultivate(XLagDynamicTerrainMapItem& cell, float DeltaTime);

	//// Добудь минерал из клетки.
	//virtual bool ExtractMineral(XLagDynamicTerrainMapItem& cell, const FXLagMineralDesc mineral, float DeltaTime);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsCultivating = false;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Miner Working")
	//	bool  IsExtracting = false;

	//// Объем добытого минерала.
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Miner Working")
	//	float  ExtractedMineralQuantity = 0.0f;


private:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Farmer; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }

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
