#pragma once
#include "ITerrainElementTransofmCondition.h"
#include "../TerrainElementEnum.h"
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
	
		for (auto x = start_x; x <= end_x; x++)
		{
			for (auto y = start_y; y <= end_y; y++)
			{
				if (x == 0 && y == 0)
					continue;

				auto pointXY = accessor->PointConst(x, y).Get();
				if (pointXY->LayerKind == _firstElement)
				{
					return true;
				}
			}
		}
		return false;
	}
private:
	const TerrainElementEnum _firstElement;
};