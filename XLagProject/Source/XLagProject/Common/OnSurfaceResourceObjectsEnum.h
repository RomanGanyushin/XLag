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
	//// Урожай
	Crop = 3
};