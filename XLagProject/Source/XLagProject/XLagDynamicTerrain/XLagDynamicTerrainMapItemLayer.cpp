#include "XLagDynamicTerrainMapItemLayer.h"

XLagDynamicTerrainMapItemLayer::XLagDynamicTerrainMapItemLayer(float level, TerrainElementEnum element)
	: _level(level), _element(element), _mineralId(0)
{
}

XLagDynamicTerrainMapItemLayer::XLagDynamicTerrainMapItemLayer(float level, TerrainElementEnum element, int mineralId)
	: _level(level), _element(element), _mineralId(mineralId)
{
}

bool XLagDynamicTerrainMapItemLayer::IsTerrainElement(const TerrainElementEnum element) const
{
	return element == _element;
}

float XLagDynamicTerrainMapItemLayer::GetLevel() const
{
	return _level;
}

void XLagDynamicTerrainMapItemLayer::ChangeLevel(const float& newLevel)
{
	_level = newLevel;
}

int XLagDynamicTerrainMapItemLayer::GetTerrainElement() const
{
	return _element;
}

void XLagDynamicTerrainMapItemLayer::ChangeTerrainElement(const TerrainElementEnum newElement)
{
	_element = newElement;
}

int XLagDynamicTerrainMapItemLayer::GetMineralId() const
{
	return _mineralId;
}
