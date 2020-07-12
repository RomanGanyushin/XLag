#pragma once

#include "../../Common/ITerrainMapAccessor.h"
#include "../Filters/ZeroPlaceMapItemFilter.h"

struct MinMaxLevelPlace
{
	MinMaxLevelPlace(std::shared_ptr<ITerrainMapAccessor> accessor)
		:_accessor(accessor)
	{
	}

	const std::pair<int,int> FindMinimalLevel()
	{
		auto result = std::make_pair(0, 0);
		auto minimal = 1e20f; 

		for (int i = 0; i < _accessor->SizeX(); i++)
		{
			for (int j = 0; j < _accessor->SizeY(); j++)
			{
				auto pos = _accessor->GetWorldPosition(i, j, GetPositionEnum::CenterLowPosition);
				if (pos.Z < minimal)
				{
					result = std::make_pair(i, j);
					minimal = pos.Z;
				}
			}
		}

		return result;
	}

	const std::pair<int, int> FindMaximalLevel()
	{
		auto result = std::make_pair(0, 0);
		auto maximal = -1e20f;

		for (int i = 0; i < _accessor->SizeX(); i++)
		{
			for (int j = 0; j < _accessor->SizeY(); j++)
			{
				auto pos = _accessor->GetWorldPosition(i, j, GetPositionEnum::CenterLowPosition);
				if (pos.Z > maximal)
				{
					result = std::make_pair(i, j);
					maximal = pos.Z;
				}
			}
		}

		return result;
	}

	std::shared_ptr<ITerrainMapAccessor> _accessor;
};