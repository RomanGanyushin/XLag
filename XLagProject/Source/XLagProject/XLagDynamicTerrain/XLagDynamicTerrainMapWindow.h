#pragma once
#include "../Common/ITerrainMapAccessor.h"

// ��������� �������� ������� � �����.
class XLagDynamicTerrainMapWindow : public ITerrainMapAccessor
{
private:
	// ��������� ������ �����.
	ITerrainMapAccessor *_fullMap;

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
	XLagDynamicTerrainMapWindow(ITerrainMapAccessor *map, int off_x, int off_y, int width, int height);

	// #inhereddoc
	const int SizeX() const override { return _width; }

	// #inhereddoc
	const int SizeY() const override { return _height; }

	// #inhereddoc
	const int OffsetX() const override { return _offsetX; }

	// #inhereddoc
	const int OffsetY() const override { return _offsetY; }

	// #inhereddoc
	const int MapLenght() const override { return _width * _height; }

	bool Validate(int const &x, int const &y) const override;

	// #inhereddoc
	std::shared_ptr<ITerrainMapAccessor> CreateWindow(int const &x, int const &y, int const &sx, int const &sy) override;

	// #inhereddoc
	FXLagDynamicTerrainMapItem& Point(int const &x, int const &y) override;
	const FXLagDynamicTerrainMapItem& PointConst(int const &x, int const &y) const override;

	// #inhereddoc
	FXLagDynamicTerrainMapItem& Point(int const &index) override;

	// #inhereddoc
	const FVector GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const override;

	// #inhereddoc
	const FVector GetWorldPosition(FXLagDynamicTerrainMapItem* item, GetPositionEnum flag) const override;

	// #inhereddoc
	const FVector GetWorldPosition(const int32 index, GetPositionEnum flag) const override;

	// #inhereddoc
	const FVector GetWorldPosition(const CoordinatePoint& coord, GetPositionEnum flag) const override;

	std::vector<FXLagDynamicTerrainMapItem*> GetFilteredItems(const IMapItemFilter& filter) override;

	bool IsChanged() override;

	const CoordinatePoint GetCoordinate(FXLagDynamicTerrainMapItem* item) const override;
};