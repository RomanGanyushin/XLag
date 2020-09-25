#pragma once
#include "OccurrenceMineralTypeEnum.h"
#include "OccurrenceMineralGenDesc.h"
#include "..\..\Common\TerrainElementEnum.h"

#include "XLagMineralDesc.generated.h"

USTRUCT(BlueprintType) 
struct FXLagMineralDesc
{
	GENERATED_BODY()

	// ��������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;

	// �������������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int ID;

	// ��������, ������������ ��� ������ ���������� ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool SearchRequire;

	// ��� ���������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<OccurrenceMineralTypeEnum> OccurrenceMineralType;

	// �������� ��������, �������������� ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<TerrainElementEnum> MineralTerrainElement;

	// �������� ������������� �������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterial* MineralPresentMaterial;

	// ������������ ������.
	// ����� � ��������, ������������� �������� �� �������� ����������������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SearchComplexity;
	
	// ������������ ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MiningComplexity;

	// ��������� ���������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FOccurrenceMineralGenDesc OccurrenceMineralGenDesc;
};