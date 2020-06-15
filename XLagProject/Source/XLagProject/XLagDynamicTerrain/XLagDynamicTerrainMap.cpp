#include "XLagDynamicTerrainMap.h"

XLagDynamicTerrainMap::XLagDynamicTerrainMap(int sizeX, int sizeY)
	: _sizeX(sizeX), _sizeY (sizeY)
{
}

void XLagDynamicTerrainMap::Initialize()
{
	Map = new XLagDynamicTerrainMapItem[MapLenght()];
}