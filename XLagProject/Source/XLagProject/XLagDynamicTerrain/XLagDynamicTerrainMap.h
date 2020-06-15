#pragma once

#include "XLagDynamicTerrainMapItem.h"

class XLagDynamicTerrainMap
{
public:
	XLagDynamicTerrainMap(int sizeX, int sizeY);
	void Initialize();

public:
	inline const int MapLenght() const { return _sizeX * _sizeY; }
	inline const int SizeX() const { return _sizeX; }
	inline const int SizeY() const { return _sizeY; }
	inline XLagDynamicTerrainMapItem& Point(int x, int y) { return Map[x + y * SizeX()]; }
	inline XLagDynamicTerrainMapItem& Point(int index) { return Map[index]; }
private:
	int _sizeX;
	int _sizeY;
	XLagDynamicTerrainMapItem *Map;
};
