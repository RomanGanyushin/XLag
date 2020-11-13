#pragma once
#include "../Common/XLagObjectProperties.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "XLagDynamicObject.generated.h"

UENUM(BlueprintType)
enum LagDynamicObjectType
{
	Tree_
};

USTRUCT(BlueprintType)
struct FXLagDynamicObject : public  FXLagObjectProperties
{
	GENERATED_BODY()

	/// Тип объекта.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
		TEnumAsByte<LagDynamicObjectType> ObjectType;

	/// Связанные клетки.
	UPROPERTY(SaveGame)
		TArray<uint32> BindedMapItemIndexes;
};