#pragma once
#include "XLagDynamicTerrainMapItem.h"
#include "../XLagGeometry/GeometryPrimitives.h"
#include "../Common/ITerrainMapAccessor.h"
#include "../Common/IMapItemFilter.h"
#include "XLagDynamicTerrainMap.h"
#include "XLagDynamicTerrainMapWindow.h"
#include "XLagDynamicTerrainMapItemOperation.h"

class XLagDynamicTerrainMapAccessor : public ITerrainMapAccessor
{
public:
	XLagDynamicTerrainMapAccessor(FXLagDynamicTerrainMap& dynamicTerrainMap)
		:_dynamicTerrainMap(dynamicTerrainMap)
	{
	}

public:

	const int SizeX() const override { return _dynamicTerrainMap.SizeX; }
	const int SizeY() const override { return _dynamicTerrainMap.SizeY; }
	const int MapLenght() const override { return  _dynamicTerrainMap.SizeX *  _dynamicTerrainMap.SizeY; }

	std::shared_ptr<ITerrainMapAccessor>  CreateWindow(int const &x, int const &y, int const &sx, int const &sy)
	{
		return std::make_shared<XLagDynamicTerrainMapWindow>(this, x, y, sx, sy);
	}

	FXLagDynamicTerrainMapItem& Point(int const &x, int const &y) override { return _dynamicTerrainMap.Map[x + y * SizeX()]; }
	const FXLagDynamicTerrainMapItem& PointConst(int const &x, int const &y) const override { return _dynamicTerrainMap.Map[x + y * SizeX()]; }
	FXLagDynamicTerrainMapItem& Point(int const &index) override { return _dynamicTerrainMap.Map[index]; }

	const FVector GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const
	{
		auto lev00 = XLagDynamicTerrainMapItemOperation(PointConst(SafeX(x), SafeY(y))).GetTopLevel();
		auto lev01 = XLagDynamicTerrainMapItemOperation(PointConst(SafeX(x), SafeY(y + 1))).GetTopLevel();
		auto lev11 = XLagDynamicTerrainMapItemOperation(PointConst(SafeX(x + 1), SafeY(y + 1))).GetTopLevel();
		auto lev10 = XLagDynamicTerrainMapItemOperation(PointConst(SafeX(x + 1), SafeY(y))).GetTopLevel();

		auto scale = _dynamicTerrainMap.Scale;

		switch (flag)
		{
		case GetPositionEnum::CenterLowPosition:
			return FVector(x * scale + scale / 2.f, y * scale + scale / 2.f, std::min(std::min(lev00, lev01), std::min(lev11, lev10)));

		case GetPositionEnum::CenterHeghtPosition:
			return FVector(x * scale + scale / 2.f, y * scale + scale / 2.f, std::max(std::max(lev00, lev01), std::max(lev11, lev10)));

		case GetPositionEnum::LeftTopPosition:
			return FVector(x * scale, (y + 1) * scale, lev01);

		case GetPositionEnum::LeftBottomPosition:
			return FVector(x * scale, y * scale, lev00);

		case GetPositionEnum::RightTopPosition:
			return FVector((x + 1) * scale, (y + 1) * scale, lev11);

		case GetPositionEnum::RightBottomPosition:
			return FVector((x + 1) * scale, y * scale, lev10);

		default:
			return FVector();
		}
	}

	const FVector GetWorldPosition(FXLagDynamicTerrainMapItem* item, GetPositionEnum flag) const
	{
		const auto coord = GetCoordinate(item);
		return GetWorldPosition(coord.X, coord.Y, flag);
	}

	const FVector GetWorldPosition(const CoordinatePoint& coord, GetPositionEnum flag) const
	{
		return GetWorldPosition(coord.X, coord.Y, flag);
	}

	// #inhereddoc
	std::vector<FXLagDynamicTerrainMapItem*> GetFilteredItems(const IMapItemFilter& filter)
	{
		std::vector<FXLagDynamicTerrainMapItem*> result;

		for (auto index = 0; index < MapLenght(); index++)
		{
			if (!filter.IsMatch(_dynamicTerrainMap.Map[index]))
				continue;

			result.push_back(&_dynamicTerrainMap.Map[index]);
		}

		return result;
	}


	bool IsChanged()
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

	inline const CoordinatePoint GetCoordinate(FXLagDynamicTerrainMapItem* item) const
	{
		if (item == nullptr)
			throw std::exception("Argument null exception");

		auto index = item - &_dynamicTerrainMap.Map[0]; //TODO возможно не сраьотает

		if (index < 0 || index >= MapLenght())
			throw std::exception("Index out of array");

		return CoordinatePoint(index - (index / SizeX()) * SizeX(), index / SizeX());
	}

private:
	FXLagDynamicTerrainMap& _dynamicTerrainMap;

private:
	inline const int SafeX(const int& x) const { return x < 0 ? 0 : x >= SizeX() ? SizeX() - 1 : x; }
	inline const int SafeY(const int& y) const { return y < 0 ? 0 : y >= SizeY() ? SizeY() - 1 : y; }
};