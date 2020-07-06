#pragma once

//TODO: �������������� XLagDynamicTerrainMapItem
#include "../../XLagProject/XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
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

	// �������� ����� �� ���������� (x,y).
	virtual XLagDynamicTerrainMapItem& Point(int const &x, int const &y) = 0;

	virtual const XLagDynamicTerrainMapItem& PointConst(int const &x, int const &y) const = 0;

	// �������� ����� �� �������.
	virtual XLagDynamicTerrainMapItem& Point(int const &index) = 0;

	// �������� ���������� ����������� �� ������� x,y.
	virtual const FVector GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const  = 0;

	// �������� ���������� ����������� �� ��������.
	virtual const FVector GetWorldPosition(XLagDynamicTerrainMapItem* item, GetPositionEnum flag) const = 0;

	virtual std::vector<XLagDynamicTerrainMapItem*> GetFilteredItems(const IMapItemFilter& filter) = 0;
};