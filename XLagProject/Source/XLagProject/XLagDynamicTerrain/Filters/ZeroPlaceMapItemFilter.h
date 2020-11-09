#pragma once

#include "../../Common/IMapItemFilter.h"

class ZeroPlaceMapItemFilter : public IMapItemFilter
{
public:
	const bool IsMatch(const FXLagDynamicTerrainMapItem& item) const override
	{
		return item.IsZeroLocation;
	}
};