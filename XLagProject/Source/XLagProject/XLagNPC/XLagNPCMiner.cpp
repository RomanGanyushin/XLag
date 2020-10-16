// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagNPCMiner.h"


void AXLagNPCMiner::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}

bool AXLagNPCMiner::SearchMineral(XLagDynamicTerrainMapItem& cell, const FXLagMineralDesc mineral, float DeltaTime)
{
	auto force = DeltaTime;
	auto isComplite = cell.SearchResource(mineral, force);
	IsSearching = !isComplite;

	return isComplite;
}

bool AXLagNPCMiner::ExtractMineral(XLagDynamicTerrainMapItem& cell, const FXLagMineralDesc mineral, float DeltaTime)
{
	auto force = DeltaTime;
	auto extractedQuantity = cell.ExtractResource(mineral, force * 10);

	if (extractedQuantity == 0.0f)
	{
		IsExtracting = false;
		return true;
	}

	ExtractedMineralQuantity += extractedQuantity;

	return ExtractedMineralQuantity >= 10.0f;  // ������� � �����.
}