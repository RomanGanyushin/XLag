#pragma once
#include "XLagDynamicTerrainMap.h"
#include "ITerrainMapAccessor.h"

// ��������� �������� ������� � �����.
class XLagDynamicTerrainMapWindow : public ITerrainMapAccessor
{
private:
	// ��������� ������ �����.
	XLagDynamicTerrainMap *_fullMap;

	// ������ ����.
	int _width;

	// ������ ����.
	int _height;

	// �������� ���� ��������� �� ��� X.
	int _offsetX;

	// �������� ���� ��������� �� ��� Y.
	int _offsetY;

public:
	// ������������� ����� ��������� ������.
	XLagDynamicTerrainMapWindow(XLagDynamicTerrainMap *map, int width, int height);

	// #inhereddoc
	const int SizeX() const override { return _width; }

	// #inhereddoc
	const int SizeY() const override { return _height; }

	// #inhereddoc
	const int MapLenght() const override { return _width * _height; }

	// #inhereddoc
	XLagDynamicTerrainMapItem& Point(int const &x, int const &y) override;
	const XLagDynamicTerrainMapItem& PointConst(int const &x, int const &y) const override;

	// #inhereddoc
	XLagDynamicTerrainMapItem& Point(int const &index) override;
};