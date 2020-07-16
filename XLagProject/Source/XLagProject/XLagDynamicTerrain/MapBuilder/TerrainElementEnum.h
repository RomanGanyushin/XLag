#pragma once

// Перечислитель элементов земли.
enum TerrainElementEnum
{	
	// Земля с дикой растительностью.
	GraundGrass,
	
	// Склальная порода.
	RockSandstone,
	GroundGrassToRockSandstoneTrans,
	RockBasalt,
	GrondGrassToRockBasaltTrans,
	RockSandstoneToRockBasaltTrans
};

class TransitionTerrainElementCatalog
{
public:
	static TerrainElementEnum For(TerrainElementEnum elem1, TerrainElementEnum elem2)
	{
		if (elem1 == elem2)
		{
			return elem1;
		}

		if ((elem1 == TerrainElementEnum::GraundGrass && elem2 == TerrainElementEnum::RockBasalt)
			|| (elem2 == TerrainElementEnum::GraundGrass && elem1 == TerrainElementEnum::RockBasalt))
		{
			return TerrainElementEnum::GrondGrassToRockBasaltTrans;
		}

		if ((elem1 == TerrainElementEnum::GraundGrass && elem2 == TerrainElementEnum::RockSandstone)
			|| (elem2 == TerrainElementEnum::GraundGrass && elem1 == TerrainElementEnum::RockSandstone))
		{
			return TerrainElementEnum::GroundGrassToRockSandstoneTrans;
		}

		if ((elem1 == TerrainElementEnum::RockSandstone && elem2 == TerrainElementEnum::RockBasalt)
			|| (elem2 == TerrainElementEnum::RockSandstone && elem1 == TerrainElementEnum::RockBasalt))
		{
			return TerrainElementEnum::RockSandstoneToRockBasaltTrans;
		}

		return elem1;
	}
};