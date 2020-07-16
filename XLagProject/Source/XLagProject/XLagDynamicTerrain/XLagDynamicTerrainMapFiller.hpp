#pragma once
#include "XLagDynamicTerrainMap.h"
//#include "Perlin2DAlgorithm.hpp"


class XLagDynamicTerrainMapFiller 
{
public:

	void TranslateTo(XLagDynamicTerrainMap *map, float fromLevel, int kind, int kind2)
	{
		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{
				auto level = map->Point(ix, iy).GetTopLevel();
				if (level > fromLevel)
				{
					map->Point(ix, iy).ChangeTopKind(kind);
				}					
			}
		}

		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{
				if (map->Point(ix, iy).GetTopKind() == kind)
				{
					for(int iix =-1; iix<=1; iix++)
						for (int iiy = -1; iiy <= 1; iiy++)
						{
							auto near_x = ix + iix;
							auto near_y = iy + iiy;

							if (iix != 0 && iiy != 0 && (near_x) >= 0 && (near_x) < map->SizeX()
								&& (near_y) >= 0 && (near_y) < map->SizeY())
							{
								if (map->Point(near_x, near_y).GetTopKind() != kind && map->Point(near_x, near_y).GetTopKind() != kind2)
								{
									map->Point(ix, iy).ChangeTopKind(kind2);
								}
							}
						}
				}
			}
		}
	}
	
	/*void FillPerlin(XLagDynamicTerrainMap *map, int kind)
	{
		auto alg = new  Perlin2DAlgorithm(time(0));

		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{
				auto level = alg->Noise((float)ix / 100.0, (float)iy / 100.0, 5) * 5000.0;
				map->Point(ix, iy).Stack.push_back(TerrainMapItemLevel(level, kind));
			}
		}
	}*/
};