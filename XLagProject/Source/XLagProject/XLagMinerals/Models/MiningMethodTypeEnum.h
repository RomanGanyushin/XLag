#pragma once
#include "MiningMethodTypeEnum.generated.h"

// ���� ������.
UENUM(BlueprintType)
enum MiningMethodTypeEnum
{
	// ������� ������.
	SimpleTake UMETA(DisplayName = "Simple Take"),

	// �������� ������ ������.
	OpencastMining UMETA(DisplayName = "Opencast Mining"),

	// ������� ������ ������.
	WellMining UMETA(DisplayName = "Classic Mining"),
};
