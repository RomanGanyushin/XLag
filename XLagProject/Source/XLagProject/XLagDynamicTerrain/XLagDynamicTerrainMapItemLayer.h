#pragma once
#include "../Common/TerrainElementEnum.h"

class XLagDynamicTerrainMapItemLayer
{
public:
	XLagDynamicTerrainMapItemLayer(float level, TerrainElementEnum element);

	XLagDynamicTerrainMapItemLayer(float level, TerrainElementEnum element, int mineralId);

	bool IsTerrainElement(const TerrainElementEnum element) const;
	float GetLevel() const;
	void ChangeLevel(const float& newLevel);
	int GetTerrainElement() const;
	void ChangeTerrainElement(const TerrainElementEnum newElement);
	int GetMineralId() const;

private:
	float _level;
	TerrainElementEnum _element;
	int _mineralId;
};