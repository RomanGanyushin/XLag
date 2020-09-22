#pragma once

#include "XLagDynamicTerrainMapItem.h"
#include "Geometry/Geometry.h"
#include "../Common/ITerrainMapAccessor.h"
#include "../Common/IMapItemFilter.h"

class XLagDynamicTerrainMap : public ITerrainMapAccessor
{
public:
	XLagDynamicTerrainMap(int sizeX, int sizeY, int scale);
	void Initialize();

public:

	const int SizeX() const override { return _sizeX; }
	const int SizeY() const override { return _sizeY; }
	const int MapLenght() const override { return _sizeX * _sizeY; }
	const float Scale;

	std::shared_ptr<ITerrainMapAccessor> CreateWindow(int const &x, int const &y, int const &sx, int const &sy) override;

    XLagDynamicTerrainMapItem& Point(int const &x, int const &y) override { return Map[x + y * SizeX()]; }
	const XLagDynamicTerrainMapItem& PointConst(int const &x, int const &y) const override { return Map[x + y * SizeX()]; }
	XLagDynamicTerrainMapItem& Point(int const &index) override { return Map[index]; }

	// #inhereddoc
	const FVector GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const override;

	// #inhereddoc
	const FVector GetWorldPosition(XLagDynamicTerrainMapItem* item, GetPositionEnum flag) const override;

	// #inhereddoc
	std::vector<XLagDynamicTerrainMapItem*> GetFilteredItems(const IMapItemFilter& filter) override;

	// #inhereddoc
	bool IsChanged() override;

private:
	int _sizeX;
	int _sizeY;
	XLagDynamicTerrainMapItem *Map;
	
	void CreateMineralLayerEventHandler(XLagDynamicTerrainMapItem* sender, const FXLagMineralDesc& mineral);

private:
	inline const int SafeX(const int x) const { return x < 0 ? 0 : x >= _sizeX ? _sizeX - 1 : x; }
	inline const int SafeY(const int y) const { return y < 0 ? 0 : y >= _sizeY ? _sizeY - 1 : y; }
	
	inline const CoordinatePoint GetCoordinate(XLagDynamicTerrainMapItem* item) const
	{
		if (item == nullptr)
			throw std::exception("Argument null exception");

		auto index = item - &Map[0];

		if (index < 0 || index >= MapLenght())
			throw std::exception("Index out of array");

		return CoordinatePoint(index - (index / SizeX()) * SizeX(), index / SizeX());
	}
};
