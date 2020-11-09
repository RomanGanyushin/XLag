#pragma once
#include "../../Common/IMapItemFilter.h"
#include "../../Common/TerrainElementEnum.h"
#include "../XLagDynamicTerrainMapItemOperation.h"

class ResourcePlacementMapItemFilter : public IMapItemFilter
{
public:
	ResourcePlacementMapItemFilter(const TerrainElementEnum element)
		:_element(element)
	{
	}

	const bool IsMatch(const FXLagDynamicTerrainMapItem& item) const override
	{
		return XLagDynamicTerrainMapItemOperation(item).GetTopKind() == _element
			   && !item.IsZeroLocation
			   && item.OnSurfaceResourceObjects == OnSurfaceResourceObjectsEnum::Empty;
	}

private:
	const TerrainElementEnum _element;
};