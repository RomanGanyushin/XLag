#pragma once
#include "OccurrenceMineralTypeEnum.generated.h"

// ��� ��������� �������� ����������.
UENUM(BlueprintType)
enum OccurrenceMineralTypeEnum
{
	// �� �����������.
	OnSurface UMETA(DisplayName = "On Surface"),

	// ��������� ��� ������������.
	UnderNearSurface UMETA(DisplayName = "Under Near Surface"),

	// ��������� ��� ������������.
	UnderDeepSurface UMETA(DisplayName = "Under Deep Surface"),
};
