#pragma once
#include "XLagDynamicTerrainMap.h"
#include "XLagDynamicTerrainMapAccessor.h"

class XLagDynamicTerrainMapInitializer
{
public:
	XLagDynamicTerrainMapInitializer(FXLagDynamicTerrainMap& dynamicTerrainMap)
		:_dynamicTerrainMap(dynamicTerrainMap)
	{
	}

	void DoInitialize()
	{
		XLagDynamicTerrainMapAccessor accesor(_dynamicTerrainMap);

		for (int x = 0; x < _dynamicTerrainMap.SizeX; x++)
			for (int y = 0; y < _dynamicTerrainMap.SizeY; y++)
			{
				accesor.Point(x, y).B[0] = &accesor.Point(SafeX(x - 1), SafeY(y - 1));
				accesor.Point(x, y).B[1] = &accesor.Point(SafeX(x - 1), SafeY(y));
				accesor.Point(x, y).B[2] = &accesor.Point(SafeX(x - 1), SafeY(y + 1));
				accesor.Point(x, y).B[3] = &accesor.Point(SafeX(x), SafeY(y + 1));
				accesor.Point(x, y).B[4] = &accesor.Point(SafeX(x + 1), SafeY(y + 1));
				accesor.Point(x, y).B[5] = &accesor.Point(SafeX(x + 1), SafeY(y));
				accesor.Point(x, y).B[6] = &accesor.Point(SafeX(x + 1), SafeY(y - 1));
				accesor.Point(x, y).B[7] = &accesor.Point(SafeX(x), SafeY(y + 1));
			}

		for (int index = 0; index < _dynamicTerrainMap.SizeX * _dynamicTerrainMap.SizeY; index++)
		{
			_dynamicTerrainMap.Map[index].Index = index;
			_dynamicTerrainMap.Map[index].CreateMineralLayerEventRaise = _bindingCreateMineralLayerEvent;
		}
	}

	void BindCreateMineralLayerEventHandler(std::function<void(FXLagDynamicTerrainMapItem*, const FXLagMineralDesc& mineral)> bindingCreateMineralLayerEvent)
	{
		_bindingCreateMineralLayerEvent = bindingCreateMineralLayerEvent;
	}

private:
	FXLagDynamicTerrainMap& _dynamicTerrainMap;
	std::function<void(FXLagDynamicTerrainMapItem*, const FXLagMineralDesc& mineral)> _bindingCreateMineralLayerEvent;
	std::function<TArray<FXLagDynamicObject*>(const int32 index)> _bindingSetFindSelfObjectsEvent;
private:
	inline const int SafeX(const int& x) const { return x < 0 ? 0 : x >= _dynamicTerrainMap.SizeX ? _dynamicTerrainMap.SizeX - 1 : x; }
	inline const int SafeY(const int& y) const { return y < 0 ? 0 : y >= _dynamicTerrainMap.SizeY ? _dynamicTerrainMap.SizeY - 1 : y; }
};