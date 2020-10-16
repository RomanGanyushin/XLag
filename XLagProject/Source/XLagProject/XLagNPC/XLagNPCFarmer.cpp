#include "XLagNPCFarmer.h"

void AXLagNPCFarmer::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}


bool AXLagNPCFarmer::Plough(XLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto force = DeltaTime;
	auto plough = force;

	auto isComplite = false;
	auto currentTopKind = cell.GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
	{
		if (currentTopKind != TerrainElementEnum::GraundGrass) //
		{
			isComplite = true;
			IsPloughing = false;
			return true;
		}
		else
		{
			cell.Pour(plough, TerrainElementEnum::Cultivated);
		}
	}
	else
	{
		cell.Pour(plough, TerrainElementEnum::Cultivated);
	}

	isComplite = cell.GetHeghtTopLevel() > 10;
	IsPloughing = !isComplite;

	return isComplite;
}

bool AXLagNPCFarmer::Sow(XLagDynamicTerrainMapItem& cell, const FXLagCropDescription& crop, float DeltaTime)
{
	return true;
}