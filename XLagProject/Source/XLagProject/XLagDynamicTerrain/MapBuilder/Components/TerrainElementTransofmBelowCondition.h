#pragma once
#include "ITerrainElementTransofmCondition.h"

class TerrainElementTransofmBelowCondition : public ITerrainElementTransofmCondition
{
public:

	TerrainElementTransofmBelowCondition(const int height)
		:_height(height)
	{

	}

	const bool IsCondition(const ITerrainMapAccessor *const accessor, const int& ix, const int& iy) const
	{
		return accessor->PointConst(ix, iy).GetTopLevel() <= _height;
	}
private:
	const int _height;
};