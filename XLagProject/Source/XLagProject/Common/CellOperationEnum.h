#pragma once
#include "CellOperationEnum.generated.h"

UENUM(BlueprintType)
enum CellOperationEnum
{
	Sow,
	Grow,
	// ��������� ������� ���������� ��������.
	Evolution,
	// ��������� ����� ����������� ��� ���������� ��������.
	EvolutionTime,
	CropQuantity,

	// ���������� ������ ����� ��������
	SearchMineral,
};