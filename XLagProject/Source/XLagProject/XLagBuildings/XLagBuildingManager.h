#pragma once

#include "XLagBuilding.h"
#include "XLagBuildingManager.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagBuildingManager : public AActor
{
	GENERATED_BODY()
	AXLagBuildingManager();

	// Коллекция построек.
	UPROPERTY() TArray<AXLagBuilding*> BuildingCollection;
};