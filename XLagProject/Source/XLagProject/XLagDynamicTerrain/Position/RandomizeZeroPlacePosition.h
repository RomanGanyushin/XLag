#pragma once

#include "../../Common/ITerrainMapAccessor.h"
#include "../Filters/ZeroPlaceMapItemFilter.h"

struct RandomizeZeroPlacePosition
{
	RandomizeZeroPlacePosition(std::shared_ptr<ITerrainMapAccessor> accessor)
		:_accessor(accessor)
	{
	}

	const FVector Get() 
	{
		auto randomPlace = GetCell();
		auto locator = _accessor->GetWorldPosition(randomPlace, GetPositionEnum::CenterHeghtPosition);
		return locator;
	}

	FXLagDynamicTerrainMapItem* GetCell()
	{
		auto zeroPlace = _accessor->GetFilteredItems(ZeroPlaceMapItemFilter());
		auto randomPlace = zeroPlace[rand() % zeroPlace.size()];
		return randomPlace;
	}

	std::shared_ptr<ITerrainMapAccessor> _accessor;
};