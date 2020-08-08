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
	virtual void Dig(XLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer);
	virtual void Pour(XLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element);
};
