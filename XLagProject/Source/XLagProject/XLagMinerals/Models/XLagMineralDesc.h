#pragma once
#include "MiningMethodTypeEnum.h"
#include "OccurrenceMineralTypeEnum.h"
#include "..\..\Common\TerrainElementEnum.h"

#include "XLagMineralDesc.generated.h"

USTRUCT(BlueprintType) 
struct FXLagMineralDesc
{
	GENERATED_BODY()

	// ��������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;

	// ��������, ������������ ��� ������ ���������� ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool SearchRequire;

	// ����� ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<MiningMethodTypeEnum> MiningMethodType;

	// ����� ���������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<OccurrenceMineralTypeEnum> OccurrenceMineralType;

	// ��������� �������� ��������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<TerrainElementEnum> LinkedTerrainElement;

	// ������������ ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SearchComplexity;
	
	// ������������ ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MiningComplexity;
};