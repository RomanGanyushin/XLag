#pragma once
#include "XLagDynamicTerrainMap.h"
#include "Perlin2DAlgorithm.hpp"
#include <time.h>

class XLagDynamicTerrainMapFiller 
{
public:

	void TranslateTo(XLagDynamicTerrainMap *map, float fromLevel, int kind, int kind2)
	{
		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{
				auto level = map->Point(ix, iy).Stack[0].Level;
				if (level > fromLevel)
				{
					map->Point(ix, iy).Stack[0].LayerKind = kind;
				}					
			}
		}

		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{
				if (map->Point(ix, iy).Stack[0].LayerKind == kind)
				{
					for(int iix =-1; iix<=1; iix++)
						for (int iiy = -1; iiy <= 1; iiy++)
						{
							auto near_x = ix + iix;
							auto near_y = iy + iiy;

							if (iix != 0 && iiy != 0 && (near_x) >= 0 && (near_x) < map->SizeX()
								&& (near_y) >= 0 && (near_y) < map->SizeY())
							{
								if (map->Point(near_x, near_y).Stack[0].LayerKind != kind && map->Point(near_x, near_y).Stack[0].LayerKind != kind2)
								{
									map->Point(ix, iy).Stack[0].LayerKind = kind2;
								}
							}
						}
				}
			}
		}
	
	}
	
	void FillPerlin(XLagDynamicTerrainMap *map, int kind)
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
	}

	void FillAsRombe(XLagDynamicTerrainMap *map, int kind)
	{
		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{

				map->Point(ix, iy).Stack.push_back(TerrainMapItemLevel(0, kind));
			}
		}

		for (int iy = 46; iy <= 50; iy++)
		{
			for (int ip = 0; ip < iy-45; ip++)
			{
				int ix = (50 - (iy - 45)) + ip;
				map->Point(ix, iy).Stack[0].Level = -1000;
				map->Point(ix, 100- iy).Stack[0].Level = -1000;
			}
		}

		for (int ix = 1; ix < map->SizeX() -1; ix++)
		{
			for (int iy = 1; iy < map->SizeY() -1; iy++)
			{
				float os =
					map->Point(ix - 1, iy - 1).Stack[0].Level
					+ map->Point(ix - 0, iy - 1).Stack[0].Level
					+ map->Point(ix + 1, iy - 1).Stack[0].Level
					+ map->Point(ix - 1, iy - 0).Stack[0].Level
					+ map->Point(ix - 0, iy - 0).Stack[0].Level
					+ map->Point(ix + 1, iy - 0).Stack[0].Level
					+ map->Point(ix - 1, iy + 1).Stack[0].Level
					+ map->Point(ix - 0, iy + 1).Stack[0].Level
					+ map->Point(ix + 1, iy + 1).Stack[0].Level;

				map->Point(ix, 100 - iy).Stack[0].Level = os / 9;
			}
		}

		for (int ix = map->SizeX() - 2; ix > 1; ix--)
		{
			for (int iy = 1; iy < map->SizeY() - 1; iy++)
			{
				float os =
					map->Point(ix - 1, iy - 1).Stack[0].Level
					+ map->Point(ix - 0, iy - 1).Stack[0].Level
					+ map->Point(ix + 1, iy - 1).Stack[0].Level
					+ map->Point(ix - 1, iy - 0).Stack[0].Level
					+ map->Point(ix - 0, iy - 0).Stack[0].Level
					+ map->Point(ix + 1, iy - 0).Stack[0].Level
					+ map->Point(ix - 1, iy + 1).Stack[0].Level
					+ map->Point(ix - 0, iy + 1).Stack[0].Level
					+ map->Point(ix + 1, iy + 1).Stack[0].Level;

				map->Point(ix, 100 - iy).Stack[0].Level = os / 9;
			}
		}

		auto d = map->Point(50, 50).Stack[0].Level;
		
		for (int iy = 46; iy <= 50; iy++)
		{
			for (int ip = 0; ip < iy - 45; ip++)
			{
				int ix = (50 - (iy - 45)) + ip;
				map->Point(ix, iy).Stack.clear();
				map->Point(ix, 100 - iy).Stack.clear();
			}
		}

	}

	void FillAsRombeHole(XLagDynamicTerrainMap *map, int kind)
	{
		
		for (int iy = 46; iy <= 50; iy++)
		{
			for (int ip = 0; ip < iy - 45; ip++)
			{
				int ix = (50 - (iy - 45)) + ip;
				map->Point(ix, iy).Stack.push_back(TerrainMapItemLevel(-350, kind));
				map->Point(ix, 100-iy).Stack.push_back(TerrainMapItemLevel(-350, kind));
			}
		}

	}

	void FillAsHoleOuterQuad(XLagDynamicTerrainMap *map, float zLevel, float zLevelEdge, int kind)
	{
		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{
				auto isCeneter = (ix > 45) && (ix < 55) && (iy > 45) && (iy < 55);

				if (isCeneter)
					continue;

				map->Point(ix, iy).Stack.push_back(TerrainMapItemLevel(zLevel, kind));
			}
		}
	}

	void FillAsHoleInnerQuad(XLagDynamicTerrainMap *map, float zLevel, int kind)
	{
		for (int ix = 0; ix < map->SizeX(); ix++)
		{
			for (int iy = 0; iy < map->SizeY(); iy++)
			{
				auto isCeneter = (ix > 45) && (ix < 55) && (iy > 45) && (iy < 55);
				if (!isCeneter)
					continue;

				map->Point(ix, iy).Stack.push_back(TerrainMapItemLevel(zLevel, kind));
			}
		}
	}
};