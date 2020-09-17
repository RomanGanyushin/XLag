#pragma once
#include "OccurrenceMineralTypeEnum.h"
#include "OccurrenceMeneralGenDesc.h"
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

	// Тип залегания.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<OccurrenceMineralTypeEnum> OccurrenceMineralType;

	// Элеменет ланшафта, представляющий ресурс.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<TerrainElementEnum> MineralTerrainElement;

	// Трудоемкость поиска.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SearchComplexity;
	
	// Трудоемкость добычи.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MiningComplexity;

	// Параметры генерации.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FOccurrenceMeneralGenDesc OccurrenceMeneralGenDesc;
};