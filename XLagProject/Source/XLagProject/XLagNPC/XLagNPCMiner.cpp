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
	auto isComplite = cell.ExtractResource(mineral, force);
	IsExtracting = !isComplite;

	return isComplite;
}