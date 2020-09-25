#pragma once
#include "OccurrenceMineralTypeEnum.h"
#include "OccurrenceMineralGenDesc.h"
#include "..\..\Common\TerrainElementEnum.h"

#include "XLagMineralDesc.generated.h"

USTRUCT(BlueprintType) 
struct FXLagMineralDesc
{
	GENERATED_BODY()

	// Название.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;

	// Идентификатор.
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int ID;

	// Значение, показывающее что ресурс необходимо искать.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool SearchRequire;

	// Тип залегания.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<OccurrenceMineralTypeEnum> OccurrenceMineralType;

	// Элеменет ланшафта, представляющий ресурс.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<TerrainElementEnum> MineralTerrainElement;

	// Материал представления ресурса.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterial* MineralPresentMaterial;

	// Трудоемкость поиска.
	// Время в секундах, затрачиваемое мафнером со средними характеристиками.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SearchComplexity;
	
	// Трудоемкость добычи.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MiningComplexity;

	// Параметры генерации.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FOccurrenceMineralGenDesc OccurrenceMineralGenDesc;
};