#pragma once
#include "MiningMethodTypeEnum.h"
#include "OccurrenceMineralTypeEnum.h"
#include "..\..\Common\TerrainElementEnum.h"

#include "XLagMineralDesc.generated.h"

USTRUCT(BlueprintType) 
struct FXLagMineralDesc
{
	GENERATED_BODY()

	// Название.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;

	// Значение, показывающее что ресурс необходимо искать.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool SearchRequire;

	// Метод добычи.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<MiningMethodTypeEnum> MiningMethodType;

	// Метод залегания.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<OccurrenceMineralTypeEnum> OccurrenceMineralType;

	// Связанный элеменет ланшафта.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<TerrainElementEnum> LinkedTerrainElement;

	// Трудоемкость поиска.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SearchComplexity;
	
	// Трудоемкость добычи.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MiningComplexity;
};