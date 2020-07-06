#pragma once
#include "XLagDynamicTerrainMap.h"
#include "../Common/ITerrainMapAccessor.h"

// Компонент оконного доступа к карте.
class XLagDynamicTerrainMapWindow : public ITerrainMapAccessor
{
private:
	// Компонент полной карты.
	XLagDynamicTerrainMap *_fullMap;

	// Ширина окна.
	int _width;

	// Высота окна.
	int _height;

	// Смещение окна просмотра по оси X.
	int _offsetX;

	// Смещение окна просмотра по оси Y.
	int _offsetY;

public:
	// Инициализрует новый экземпляр класса.
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

	// #inhereddoc
	const FVector GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const override;

	// Получает координату простраства по элементу.
	const FVector GetWorldPosition(XLagDynamicTerrainMapItem* item, GetPositionEnum flag) const override;

	std::vector<XLagDynamicTerrainMapItem*> GetFilteredItems(const IMapItemFilter& filter) override;
};