// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "XLagDynamicTerrain/XLagDynamicTerrainMap.h"
#include "XLagProjectGameMode.generated.h"

UCLASS(minimalapi)
class AXLagProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AXLagProjectGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FXLagDynamicTerrainMap TerrainMap;
};



