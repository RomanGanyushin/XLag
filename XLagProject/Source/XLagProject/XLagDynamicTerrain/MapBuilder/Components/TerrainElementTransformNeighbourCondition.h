#pragma once
#include "ITerrainElementTransofmCondition.h"
#include "../../../Common/TerrainElementEnum.h"
#include <algorithm>

class TerrainElementTransformNeighbourCondition : public ITerrainElementTransofmCondition
{
public:

	TerrainElementTransformNeighbourCondition(const TerrainElementEnum firstElement)
		:_firstElement(firstElement)
	{

	}

	const bool IsCondition(const ITerrainMapAccessor *const accessor, const int& ix, const int& iy) const
	{
		static int start_x, end_x, start_y, end_y;
		start_x = std::max(0, ix - 1);
		start_y = std::max(0, iy - 1);
		end_x = std::min(accessor->SizeX() -1, ix + 1);
		end_y = std::min(accessor->SizeY() -1, iy + 1);
		
		if (accessor->PointConst(start_x, iy).Get()->GetTerrainElement() == _firstElement)
			return true;

		if (accessor->PointConst(end_x, iy).Get()->GetTerrainElement() == _firstElement)
			return true;

		if (accessor->PointConst(ix, start_y).Get()->GetTerrainElement() == _firstElement)
			return true;

		if (accessor->PointConst(ix, end_y).Get()->GetTerrainElement() == _firstElement)
			return true;

		return false;
	}
private:
	const TerrainElementEnum _firstElement;
};