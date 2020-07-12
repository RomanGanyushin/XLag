// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagNPCMiner.h"

void AXLagNPCMiner::Dig(XLagDynamicTerrainMapItem& cell, float toLevel)
{
	auto targetSlice = cell.Get()->Level - toLevel;

	UE_LOG(LogTemp, Log, TEXT("Dig target slice %f"), targetSlice);

	if (targetSlice <= 0)
		return;

	targetSlice = std::min(targetSlice, 5.f);
	cell.Dig(targetSlice);
}