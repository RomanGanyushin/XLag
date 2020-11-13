#pragma once
#include <functional>
#include "XLagDynamicTerrainMapItemLayer.h"
#include "../Common/CellOperationEnum.h"
#include "../Common/OnSurfaceResourceObjectsEnum.h"
#include "../XLagMinerals/Models/XLagMineralDesc.h"
#include "XLagDynamicTerrainMapItem.generated.h"
   
USTRUCT(BlueprintType)
struct FXLagDynamicTerrainMapItem
{
	GENERATED_BODY()

		FXLagDynamicTerrainMapItem()
	{
		static int64 id_counter = 0;
		Id = id_counter++;
		OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Empty;
		IsZeroLocation = false;
		Changed = false;
	}

	UPROPERTY()
	int32 Id;

	UPROPERTY()
	int32 Index;
	
	UPROPERTY()
	TArray<FXLagDynamicTerrainMapItemLayer> Stack;

	UPROPERTY()
	TMap<TEnumAsByte<CellOperationEnum>, float> OperationTimeMap;

	UPROPERTY()
	TEnumAsByte<OnSurfaceResourceObjectsEnum> OnSurfaceResourceObjects;

	UPROPERTY()
	bool IsZeroLocation;

	UPROPERTY()
	bool Changed;

	FXLagDynamicTerrainMapItem* B[8];
	std::function<void(FXLagDynamicTerrainMapItem*, const FXLagMineralDesc& mineral)> CreateMineralLayerEventRaise;
};