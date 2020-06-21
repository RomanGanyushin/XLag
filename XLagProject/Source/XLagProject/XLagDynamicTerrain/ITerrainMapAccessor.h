#pragma once
#include "XLagDynamicTerrainMapItem.h"

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
};