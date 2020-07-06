#pragma once
#include "../../Common/IMapItemFilter.h"
#include "../MapBuilder/TerrainElementEnum.h"

class ResourcePlacementMapItemFilter : public IMapItemFilter
{
public:
	ResourcePlacementMapItemFilter(const TerrainElementEnum element)
		:_element(element)
	{
	}

	const bool IsMatch(const XLagDynamicTerrainMapItem& item) const override
	{
		return item.Get()->LayerKind == _element 
			   && !item.IsZeroLocation
			   && item.OnSurfaceResourceObjects == OnSurfaceResourceObjectsEnum::Empty;
	}

private:
	const TerrainElementEnum _element;
};