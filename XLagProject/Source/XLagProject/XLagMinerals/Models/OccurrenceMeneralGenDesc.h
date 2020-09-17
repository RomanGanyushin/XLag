#pragma once

#include "..\..\Common\TerrainElementEnum.h"
#include "OccurrenceMeneralGenDesc.generated.h"

USTRUCT(BlueprintType)
struct FOccurrenceMeneralGenDesc
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