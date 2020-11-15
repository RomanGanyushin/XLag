#pragma once
#include <memory>
//TODO: �������������� XLagDynamicTerrainMapItem
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagGeometry/GeometryPrimitives.h"
#include "GetPositionEnum.h"
#include "IMapItemFilter.h"

// ��������� ������� � �����.
struct ITerrainMapAccessor
{
	// ����������� ����������.
	virtual ~ITerrainMapAccessor() = default;

	// �������� ������ �� ��� X. 
	virtual const int SizeX() const = 0;

	// �������� ������ �� ��� Y.
	virtual const int SizeY() const = 0;

	// �������� ������ �����.
	virtual const int MapLenght() const = 0;

	// ������� ����.
	virtual std::shared_ptr<ITerrainMapAccessor> CreateWindow(int const &x, int const &y, int const &sx, int const &sy) = 0;

	// �������� ����� �� ���������� (x,y).
	virtual FXLagDynamicTerrainMapItem& Point(int const &x, int const &y) = 0;

	virtual const FXLagDynamicTerrainMapItem& PointConst(int const &x, int const &y) const = 0;

	// �������� ����� �� �������.
	virtual FXLagDynamicTerrainMapItem& Point(int const &index) = 0;

	// �������� ���������� ����������� �� x,y.
	virtual const FVector GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const  = 0;

	virtual const FVector GetWorldPosition(const CoordinatePoint& coord, GetPositionEnum flag) const = 0;

	// �������� ���������� ����������� �� �������.
	virtual const FVector GetWorldPosition(const int32 index, GetPositionEnum flag) const = 0;

	// �������� ���������� ����������� �� ��������.
	virtual const FVector GetWorldPosition(FXLagDynamicTerrainMapItem* item, GetPositionEnum flag) const = 0;

	virtual std::vector<FXLagDynamicTerrainMapItem*> GetFilteredItems(const IMapItemFilter& filter) = 0;

	virtual const CoordinatePoint GetCoordinate(FXLagDynamicTerrainMapItem* item) const = 0;

	virtual bool IsChanged() = 0;
};