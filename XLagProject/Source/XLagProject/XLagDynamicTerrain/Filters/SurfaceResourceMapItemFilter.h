#pragma once
#include "../../Common/IMapItemFilter.h"
#include "../../Common/OnSurfaceResourceObjectsEnum.h"
#include "../../Common/TerrainElementEnum.h"

class SurfaceResourceMapItemFilter : public IMapItemFilter
{
public:
	SurfaceResourceMapItemFilter(const OnSurfaceResourceObjectsEnum resource)
		:_resource(resource)
	{
	}

	const bool IsMatch(const FXLagDynamicTerrainMapItem& item) const override
	{
		return item.OnSurfaceResourceObjects == OnSurfaceResourceObjectsEnum::Tree;
	}

private:
	const OnSurfaceResourceObjectsEnum _resource;
};