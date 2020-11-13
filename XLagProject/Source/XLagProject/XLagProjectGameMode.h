// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "XLagDynamicTerrain/XLagDynamicTerrainMap.h"
#include "XLagDynamicObject/XLagDynamicObjects.h"
#include "XLagProjectGameMode.generated.h"


UCLASS(minimalapi)
class AXLagProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AXLagProjectGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FXLagDynamicTerrainMap TerrainMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FXLagDynamicObjects TerrainObjects;

	UFUNCTION(BlueprintCallable)
		void SetTerrainMap(const FXLagDynamicTerrainMap& map, const FXLagDynamicObjects& objects);	
};



