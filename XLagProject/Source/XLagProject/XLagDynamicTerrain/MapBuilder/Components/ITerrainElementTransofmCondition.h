#pragma once
#include "../../../Common/ITerrainMapAccessor.h"

struct ITerrainElementTransofmCondition
{
	virtual ~ITerrainElementTransofmCondition() = default;
	virtual const bool IsCondition(const ITerrainMapAccessor *const accessor, const int& ix, const int& iy) const = 0;
};