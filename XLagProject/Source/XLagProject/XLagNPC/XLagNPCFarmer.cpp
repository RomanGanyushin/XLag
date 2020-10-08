#include "XLagNPCFarmer.h"

void AXLagNPCFarmer::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}


bool AXLagNPCFarmer::Cultivate(XLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto force = DeltaTime;
	auto cultivate = force;

	auto isComplite = false;
	auto currentTopKind = cell.GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
	{
		if (currentTopKind != TerrainElementEnum::GraundGrass) //
		{
			isComplite = true;
			IsCultivating = false;
			return true;
		}
		else
		{
			cell.Pour(cultivate, TerrainElementEnum::Cultivated);
		}
	}
	else
	{
		cell.Pour(cultivate, TerrainElementEnum::Cultivated);
	}

	isComplite = cell.GetHeghtTopLevel() > 10;
	IsCultivating = !isComplite;

	return isComplite;
}

