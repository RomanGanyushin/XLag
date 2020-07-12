#pragma once
#include <vector>
#include "../../XLagProject//Common/OnSurfaceResourceObjectsEnum.h"

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
	bool IsZeroLocation = false;
	bool Changed = false;

	OnSurfaceResourceObjectsEnum OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Empty;

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

	void Dig(float value)
	{
		Stack.back().Level -= value;
		Changed = true;
	}

	const inline bool HasOnSurfaceResourceObjects(OnSurfaceResourceObjectsEnum type) const
	{
		return  OnSurfaceResourceObjects == type;
	}
};