#pragma once
#include "ITerrainElementTransofmCondition.h"
#include "../../XLagDynamicTerrainMapItemOperation.h"

class TerrainElementTransofmHigherCondition : public ITerrainElementTransofmCondition
{
public:

	TerrainElementTransofmHigherCondition(const int height)
		:_height(height)
	{
	
	}

	const bool IsCondition(const ITerrainMapAccessor *const accessor, const int& ix, const int& iy) const
	{
		return XLagDynamicTerrainMapItemOperation(accessor->PointConst(ix,iy)).GetTopLevel() >= _height;
	}
private:
	const int _height;
};