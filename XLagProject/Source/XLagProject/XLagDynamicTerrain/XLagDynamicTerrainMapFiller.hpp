#pragma once
#include "XLagDynamicTerrainMap.h"
#include "XLagDynamicTerrainMapItemOperation.h"
#include "XLagDynamicTerrainMapAccessor.h"

class XLagDynamicTerrainMapFiller 
{
public:

	void TranslateTo(XLagDynamicTerrainMapAccessor *map, float fromLevel, TerrainElementEnum kind, TerrainElementEnum kind2)
	{
		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{				
				auto level = XLagDynamicTerrainMapItemOperation(map->Point(ix, iy)).GetTopLevel();
				if (level > fromLevel)
				{
					XLagDynamicTerrainMapItemOperation(map->Point(ix, iy)).ChangeTopKind(kind);
				}					
			}
		}

		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{
				if (XLagDynamicTerrainMapItemOperation(map->Point(ix, iy)).GetTopKind() == kind)
				{
					for(int iix =-1; iix<=1; iix++)
						for (int iiy = -1; iiy <= 1; iiy++)
						{
							auto near_x = ix + iix;
							auto near_y = iy + iiy;

							if (iix != 0 && iiy != 0 && (near_x) >= 0 && (near_x) < map->SizeX()
								&& (near_y) >= 0 && (near_y) < map->SizeY())
							{
								if (XLagDynamicTerrainMapItemOperation(map->Point(near_x, near_y)).GetTopKind() != kind && XLagDynamicTerrainMapItemOperation(map->Point(near_x, near_y)).GetTopKind() != kind2)
								{
									XLagDynamicTerrainMapItemOperation(map->Point(ix, iy)).ChangeTopKind(kind2);
								}
							}
						}
				}
			}
		}
	}
};