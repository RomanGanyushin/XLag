#pragma once
#include <vector>

struct TerrainMapItemLevel
{
	TerrainMapItemLevel(float level, int layerKind)
		:Level(level), LayerKind(layerKind)
	{
	}

	float Level;
	int LayerKind;
};

class XLagDynamicTerrainMapItem
{
public:
	std::vector<TerrainMapItemLevel>  Stack;

	const TerrainMapItemLevel* GetForLayerKind(int layerKind) const
	{
		if (Stack.empty())
			return nullptr;

		auto& top = Stack.back();
		if (top.LayerKind != layerKind)
			return nullptr;
	
		return &top;
	}

	const TerrainMapItemLevel* Get() const
	{
		if (Stack.empty())
			return nullptr;

		return &Stack.back();
	}
};