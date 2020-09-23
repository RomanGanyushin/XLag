// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagMinerals/XLagMineralManager.h"
#include "XLagNPCMiner.generated.h"

/**
 * 
 */
UCLASS()
class XLAGPROJECT_API AXLagNPCMiner : public AXLagNPCBase
{
	GENERATED_BODY()

public:
	virtual void OfferAccept(UXLagTaskBase* task) override;

	// Ищи минерал в клетке.
	virtual bool SearchMineral(XLagDynamicTerrainMapItem& cell, const FXLagMineralDesc mineral, float DeltaTime);

	// Добудь минерал из клетки.
	virtual bool ExtractMineral(XLagDynamicTerrainMapItem& cell, const FXLagMineralDesc mineral, float DeltaTime);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Miner Working")
		bool  IsSearching = false;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Miner Working")
		bool  IsExtracting = false;
	
private:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Miner; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }

private:
	inline AXLagMineralManager* GetMineralManager()
	{
		static AXLagMineralManager* mineralManager = nullptr;
		if (mineralManager == nullptr)
		{
			mineralManager = AXLagMineralManager::GetMineralManager();
		}

		return mineralManager;
	}
};
