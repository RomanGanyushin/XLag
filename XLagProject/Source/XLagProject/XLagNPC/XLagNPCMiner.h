// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
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

private:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Miner; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }
};
