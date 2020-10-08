#pragma once
#include "TerrainElementEnum.generated.h"

// Перечислитель элементов земли.
UENUM(BlueprintType)
enum TerrainElementEnum
{	
	None UMETA(DisplayName = "None"),

	// Земля с дикой растительностью.
	GraundGrass UMETA(DisplayName = "Graund Grass"),
	GroundGrassToRockSandstoneTrans,
	GrondGrassToRockBasaltTrans,
	GrondGrassToCoalTrans,

	// Песок.
	RockSandstone UMETA(DisplayName = "Rock Sandstone"),
	RockSandstoneToRockBasaltTrans,
	
	// Скала.
	RockBasalt,	
	
	// Уголь.
	Coal UMETA(DisplayName = "Coal"),

	Cultivated UMETA(DisplayName = "Сultivated")

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

		if ((elem1 == TerrainElementEnum::GraundGrass && elem2 == TerrainElementEnum::Coal)
			|| (elem2 == TerrainElementEnum::GraundGrass && elem1 == TerrainElementEnum::Coal))
		{
			return TerrainElementEnum::GrondGrassToCoalTrans;
		}

		if ((elem1 == TerrainElementEnum::RockSandstone && elem2 == TerrainElementEnum::RockBasalt)
			|| (elem2 == TerrainElementEnum::RockSandstone && elem1 == TerrainElementEnum::RockBasalt))
		{
			return TerrainElementEnum::RockSandstoneToRockBasaltTrans;
		}

		return elem1;
	}
};