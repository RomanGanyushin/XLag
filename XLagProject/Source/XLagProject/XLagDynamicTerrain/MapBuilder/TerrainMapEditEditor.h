#pragma once
#include "ITerrainMapEditComponent.h"

class TerrainMapEditEditor
{
public:
	TerrainMapEditEditor(std::shared_ptr<ITerrainMapAccessor> accessor);
	void FillByXY(ITerrainMapEditComponent *component);
private:
	std::shared_ptr<ITerrainMapAccessor>_accessor;
};