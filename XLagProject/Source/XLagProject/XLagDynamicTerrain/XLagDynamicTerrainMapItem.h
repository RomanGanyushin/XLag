#pragma once
#include <functional>
#include "XLagDynamicTerrainMapItemLayer.h"
#include "../Common/CellOperationEnum.h"
#include "../XLagMinerals/Models/XLagMineralDesc.h"
#include "../XLagDynamicObject/XLagDynamicObject.h"
#include "XLagDynamicTerrainMapItem.generated.h"

USTRUCT(BlueprintType)
struct FXLagDynamicObjectRef
{
	GENERATED_BODY()

	UPROPERTY()
	int32 ObjectId;

	UPROPERTY()
	TEnumAsByte <XLagDynamicObjectType> ObjectType;
};

USTRUCT(BlueprintType)
struct FXLagDynamicTerrainMapItem
{
	GENERATED_BODY()

	FXLagDynamicTerrainMapItem()
	{
		IsZeroLocation = false;
		Changed = false;
	}

	UPROPERTY()
	int32 Index;
	
	UPROPERTY()
	TArray<FXLagDynamicTerrainMapItemLayer> Stack;

	UPROPERTY()
	TMap<TEnumAsByte<CellOperationEnum>, float> OperationTimeMap;

	UPROPERTY()
	bool IsZeroLocation;

	UPROPERTY()
	bool Changed;

	TArray<FXLagDynamicObjectRef> RefItemObjects;

	FXLagDynamicTerrainMapItem* B[8];
	std::function<void(FXLagDynamicTerrainMapItem*, const FXLagMineralDesc& mineral)> CreateMineralLayerEventRaise;
};