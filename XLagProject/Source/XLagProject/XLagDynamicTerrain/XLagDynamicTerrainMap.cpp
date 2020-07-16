#include "XLagDynamicTerrainMap.h"
#include "XLagDynamicTerrainMapWindow.h"
#include <algorithm>

XLagDynamicTerrainMap::XLagDynamicTerrainMap(int sizeX, int sizeY, int scale)
	: _sizeX(sizeX), _sizeY (sizeY), Scale(scale)
{
}

void XLagDynamicTerrainMap::Initialize()
{
	Map = new XLagDynamicTerrainMapItem[MapLenght()];

	for (int x = 0; x <_sizeX; x++)
		for (int y = 0; y < _sizeY; y++)
		{
			Point(x, y).B[0] = &Point(SafeX(x - 1), SafeY(y - 1));
			Point(x, y).B[1] = &Point(SafeX(x - 1), SafeY(y));
			Point(x, y).B[2] = &Point(SafeX(x - 1), SafeY(y + 1));
			Point(x, y).B[3] = &Point(SafeX(x ), SafeY(y + 1));
			Point(x, y).B[4] = &Point(SafeX(x + 1), SafeY(y + 1));
			Point(x, y).B[5] = &Point(SafeX(x + 1), SafeY(y));
			Point(x, y).B[6] = &Point(SafeX(x + 1), SafeY(y -1 ));
			Point(x, y).B[7] = &Point(SafeX(x), SafeY(y + 1));
		}
}

std::shared_ptr<ITerrainMapAccessor> XLagDynamicTerrainMap::CreateWindow(int const &x, int const &y, int const &sx, int const &sy)
{
	return std::shared_ptr<ITerrainMapAccessor>(new XLagDynamicTerrainMapWindow(this, x, y, sx, sy));
}

const FVector XLagDynamicTerrainMap::GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const
{
	auto lev00 = PointConst(SafeX(x), SafeY(y)).GetTopLevel();
	auto lev01 = PointConst(SafeX(x), SafeY(y + 1)).GetTopLevel();
	auto lev11 = PointConst(SafeX(x + 1), SafeY(y + 1)).GetTopLevel();
	auto lev10 = PointConst(SafeX(x + 1), SafeY(y)).GetTopLevel();

	switch (flag)
	{
		case GetPositionEnum::CenterLowPosition:
			return FVector(x * Scale + Scale / 2.f, y * Scale + Scale / 2.f, std::min(std::min(lev00, lev01), std::min(lev11, lev10)));

		case GetPositionEnum::CenterHeghtPosition:
			return FVector(x * Scale + Scale / 2.f, y * Scale + Scale / 2.f, std::max(std::max(lev00, lev01), std::max(lev11, lev10)));

		default:
			return FVector();
	}
}

const FVector XLagDynamicTerrainMap::GetWorldPosition(XLagDynamicTerrainMapItem* item, GetPositionEnum flag) const
{
	auto index = item - &Map[0];

	if (index < 0 || index >= MapLenght())
		throw std::exception("Index out of array");

	int y = index / SizeX();
	int x = index - y * SizeX();
	return GetWorldPosition(x, y, flag);
}

// #inhereddoc
std::vector<XLagDynamicTerrainMapItem*> XLagDynamicTerrainMap::GetFilteredItems(const IMapItemFilter& filter)
{
	std::vector<XLagDynamicTerrainMapItem*> result;

	for (auto index = 0; index < MapLenght(); index++)
	{
		if (!filter.IsMatch(Map[index]))
			continue;

		result.push_back(&Map[index]);
	}

	return result;
}


bool XLagDynamicTerrainMap::IsChanged()
{
	bool result = false;
	for (int ix = 0; ix < SizeX(); ix++)
		for (int iy = 0; iy < SizeX(); iy++)
		{
			if (Point(ix, iy).Changed)
			{
				result = true;
				Point(ix, iy).Changed = false;
			}
		}

	return result;
}