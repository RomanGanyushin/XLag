// Fill out your copyright notice in the Description page of Project Settings.
#include "XLagNPCMiner.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"
#include "../Common/CellOperationProcessing.h"

#define DEBUG_FORCE_MULTIPLIER 1

void AXLagNPCMiner::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}

bool AXLagNPCMiner::SearchMineral(FXLagDynamicTerrainMapItem& cell, const FXLagMineralDesc mineral, float DeltaTime)
{
	auto searchForce = DeltaTime;
	auto searchComplexity = mineral.SearchComplexity;

	auto isComplite = XLagDynamicTerrainMapItemOperation(cell).CheckForMineral(mineral.ID);
	if (!isComplite)
	{
		CellOperationProcessing operation(&cell, CellOperationEnum::SearchMineral, searchComplexity);
		operation.Increase(searchForce);
		
		if (operation.IsComplete())
		{
			isComplite = true;
			cell.CreateMineralLayerEventRaise(&cell, mineral);
		}	
	}

	IsSearching = !isComplite;

	return isComplite;
}

bool AXLagNPCMiner::ExtractMineral(FXLagDynamicTerrainMapItem& cell, const FXLagMineralDesc mineral, float DeltaTime)
{
	auto force = DeltaTime;
	auto extractingForce = force * DEBUG_FORCE_MULTIPLIER;
	auto extractedQuantity = XLagDynamicTerrainMapItemOperation(cell).ExtractResource(mineral, extractingForce);
  	if (extractedQuantity == 0.0f)
	{
		IsExtracting = false;
		return true;
	}

	ExtractedMineralQuantity += extractedQuantity;
	IsExtracting = ExtractedMineralQuantity < 10.0f;
 
	return !IsExtracting;  // Вынести в статы.
}