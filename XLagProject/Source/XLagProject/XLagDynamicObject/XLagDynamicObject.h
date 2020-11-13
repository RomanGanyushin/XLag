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

	/// ��� �������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
		TEnumAsByte<LagDynamicObjectType> ObjectType;

	/// ��������� ������.
	UPROPERTY(SaveGame)
		TArray<uint32> BindedMapItemIndexes;
};