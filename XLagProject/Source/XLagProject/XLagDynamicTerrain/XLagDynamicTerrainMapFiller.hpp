#pragma once
#include "XLagDynamicTerrainMap.h"

class XLagDynamicTerrainMapFiller 
{
public:
	
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