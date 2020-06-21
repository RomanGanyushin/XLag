#pragma once
#include "ITerrainMapEditComponent.h"

class TerrainMapEditEditor
{
public:
	TerrainMapEditEditor(ITerrainMapAccessor *const accessor);
	void FillByXY(ITerrainMapEditComponent *component);
private:
	ITerrainMapAccessor *const _accessor = nullptr;
};