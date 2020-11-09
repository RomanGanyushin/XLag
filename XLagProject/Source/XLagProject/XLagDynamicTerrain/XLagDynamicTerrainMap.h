#pragma once
#include "XLagDynamicTerrainMapItem.h"
#include "XLagDynamicTerrainMap.generated.h"

USTRUCT(BlueprintType)
struct FXLagDynamicTerrainMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TArray<FXLagDynamicTerrainMapItem> Map;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	float Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	bool IsCreated = false;
};