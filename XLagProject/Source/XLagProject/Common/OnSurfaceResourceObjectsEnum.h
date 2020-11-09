#pragma once
#include "OnSurfaceResourceObjectsEnum.generated.h"

/*
	Перечислитель ресурсов на поверхности.
*/
UENUM(BlueprintType)
enum OnSurfaceResourceObjectsEnum
{
	// Пусто.
	Empty = 0,
	// Дерево.
	Tree  = 1,
	// Камень.
	Stone = 2,
	// Урожай
	Crop = 3
};
