// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagNPCMiner.h"

void AXLagNPCMiner::Dig(XLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer)
{
	auto targetSlice = cell.GetTopLevel() - toLevel;

	UE_LOG(LogTemp, Log, TEXT("Dig target slice %f"), targetSlice);

	if (targetSlice <= 0)
		return;

	targetSlice = std::min(targetSlice, 5.f);
	cell.Dig(targetSlice, keepTopLayer);
}

void AXLagNPCMiner::Pour(XLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element)
{
	auto targetSlice = toLevel - cell.GetTopLevel();

	UE_LOG(LogTemp, Log, TEXT("Dig target slice %f"), targetSlice);

	if (targetSlice <= 0)
		return;

	targetSlice = std::min(targetSlice, 5.f);
	cell.Pour(targetSlice, element);
}


