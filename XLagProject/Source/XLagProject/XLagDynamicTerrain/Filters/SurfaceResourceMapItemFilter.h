#pragma once
#include "../../Common/IMapItemFilter.h"
#include "../XLagDynamicTerrainMapItemOperation.h"

class SurfaceResourceMapItemFilter : public IMapItemFilter
{
public:
	SurfaceResourceMapItemFilter(const XLagDynamicObjectType type)
		:_type(type)
	{
	}

	const bool IsMatch(const FXLagDynamicTerrainMapItem& item) const override
	{
		return XLagDynamicTerrainMapItemOperation::HasObjectType(item, _type);
	}

private:
	const XLagDynamicObjectType _type;
};