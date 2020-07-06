#pragma once
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"

struct IMapItemFilter
{
	virtual ~IMapItemFilter() = default;
	virtual const bool IsMatch(const XLagDynamicTerrainMapItem& item) const = 0;
};
