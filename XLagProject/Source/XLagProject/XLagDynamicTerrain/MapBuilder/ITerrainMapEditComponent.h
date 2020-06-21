#pragma once
#include "../ITerrainMapAccessor.h"

struct ITerrainMapEditComponent
{
	virtual ~ITerrainMapEditComponent() = default;
	virtual void DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy) = 0;
};