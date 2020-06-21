#pragma once

#include "XLagDynamicTerrainMapItem.h"
#include "ITerrainMapAccessor.h"

class XLagDynamicTerrainMap : public ITerrainMapAccessor
{
public:
	XLagDynamicTerrainMap(int sizeX, int sizeY);
	void Initialize();

public:

	const int SizeX() const override { return _sizeX; }
	const int SizeY() const override { return _sizeY; }
	const int MapLenght() const override { return _sizeX * _sizeY; }

    XLagDynamicTerrainMapItem& Point(int const &x, int const &y) override { return Map[x + y * SizeX()]; }
	const XLagDynamicTerrainMapItem& PointConst(int const &x, int const &y) const override { return Map[x + y * SizeX()]; }
	XLagDynamicTerrainMapItem& Point(int const &index) override { return Map[index]; }

private:
	int _sizeX;
	int _sizeY;
	XLagDynamicTerrainMapItem *Map;
};
