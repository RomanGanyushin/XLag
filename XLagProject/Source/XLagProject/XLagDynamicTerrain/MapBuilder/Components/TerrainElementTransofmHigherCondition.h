#pragma once
#include "ITerrainElementTransofmCondition.h"

class TerrainElementTransofmHigherCondition : public ITerrainElementTransofmCondition
{
public:

	TerrainElementTransofmHigherCondition(const int height)
		:_height(height)
	{
	
	}

	const bool IsCondition(const ITerrainMapAccessor *const accessor, const int& ix, const int& iy) const
	{
		return accessor->PointConst(ix,iy).GetTopLevel() >= _height;
	}
private:
	const int _height;
};