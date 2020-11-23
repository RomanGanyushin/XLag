#include "XLagNPCBuilderman.h"
#include "../BuildDefinition.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"

bool AXLagNPCBuilderman::Dig(FXLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer)
{
	XLagDynamicTerrainMapItemOperation cellOperation(cell);
	auto targetSlice = cellOperation.GetTopLevel() - toLevel;
	auto isComplite = true;

	if (targetSlice > 0)
	{
		targetSlice = std::min(targetSlice, 0.01f * DEBUG_FORCE_MULTIPLIER);
		cellOperation.Dig(targetSlice, keepTopLayer);
		isComplite = false;
	}

	IsDiging = !isComplite;
	return isComplite;
}

bool AXLagNPCBuilderman::Pour(FXLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element)
{
	XLagDynamicTerrainMapItemOperation cellOperation(cell);
	auto targetSlice = toLevel - cellOperation.GetTopLevel();
	auto isComplite = true;

	if (targetSlice > 0)
	{
		targetSlice = std::min(targetSlice, 0.01f * DEBUG_FORCE_MULTIPLIER);
		cellOperation.Pour(targetSlice, element);
		isComplite = false;
	}

	IsPouring = !isComplite;
	return isComplite;
}

void AXLagNPCBuilderman::Build(AXLagBuilding* building)
{
	IsBuilding = true;
	building->Build();
}

void AXLagNPCBuilderman::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}