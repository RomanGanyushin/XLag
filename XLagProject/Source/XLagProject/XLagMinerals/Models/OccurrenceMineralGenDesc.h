#pragma once

#include "..\..\Common\TerrainElementEnum.h"
#include "OccurrenceMineralGenDesc.generated.h"

USTRUCT(BlueprintType)
struct FOccurrenceMineralGenDesc
{
	GENERATED_BODY()

	// ������������ 0-1. 
	// 1 - ������������� ����� ����������������� � ����� �����.
	// 2 - ������������� ����� ���������� ����������� �� �����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Density;

	// ������� ���������� �������� �� 1 ��.�.
	// ����� ���������� ������� = ������� �������� ���� x AverageQuantity.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AverageQuantity;

	// ���������� ������������� �������� (� ����).
	// 0 - ���������� ������������.
	// -1 - �� ���������������.
	// n - �� ��� ���������� ����, ������������ �������� ���������� ������. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int RecoveryHalfTime;

	// �������� ��������, ��� ������� �������� ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<TerrainElementEnum> UnderTerrainElement;
};