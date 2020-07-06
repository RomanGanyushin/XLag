#pragma once

//TODO: заинтерфейсить XLagDynamicTerrainMapItem
#include "../../XLagProject/XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "GetPositionEnum.h"
#include "IMapItemFilter.h"

// Интерфейс доступа к карте.
struct ITerrainMapAccessor
{
	// Виртуальный деструктор.
	virtual ~ITerrainMapAccessor() = default;

	// Получает размер по оси X. 
	virtual const int SizeX() const = 0;

	// Получает размер по оси Y.
	virtual const int SizeY() const = 0;

	// Получает размер карты.
	virtual const int MapLenght() const = 0;

	// Получает точку по координате (x,y).
	virtual XLagDynamicTerrainMapItem& Point(int const &x, int const &y) = 0;

	virtual const XLagDynamicTerrainMapItem& PointConst(int const &x, int const &y) const = 0;

	// Получает точку по индексу.
	virtual XLagDynamicTerrainMapItem& Point(int const &index) = 0;

	// Получает координату простраства по индексу x,y.
	virtual const FVector GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const  = 0;

	// Получает координату простраства по элементу.
	virtual const FVector GetWorldPosition(XLagDynamicTerrainMapItem* item, GetPositionEnum flag) const = 0;

	virtual std::vector<XLagDynamicTerrainMapItem*> GetFilteredItems(const IMapItemFilter& filter) = 0;
};