#pragma once
#include "ITerrainElementTransofmCondition.h"
#include "../../../Common/TerrainElementEnum.h"
#include "../../XLagDynamicTerrainMapItemOperation.h"
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
		start_x = std::max(0, ix - 2);
		start_y = std::max(0, iy - 2);
		end_x = std::min(accessor->SizeX() - 1, ix + 1);
		end_y = std::min(accessor->SizeY() - 1, iy + 1);

		for (int i = start_x; i <= end_x; i++)
			for (int j = start_y; j <= end_y; j++)
			{
				if (i == ix || j == iy)
					continue;

				if (XLagDynamicTerrainMapItemOperation(accessor->PointConst(i, j)).Get()->Element == _firstElement)
					return true;
			}



		return false;
	}
private:
	const TerrainElementEnum _firstElement;
};