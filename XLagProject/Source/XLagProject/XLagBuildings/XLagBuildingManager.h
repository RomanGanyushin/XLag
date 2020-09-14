#pragma once

#include "XLagBuilding.h"
#include "XLagBuildingManager.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagBuildingManager : public AActor
{
	GENERATED_BODY()
	AXLagBuildingManager();

	// ��������� ��������.
	UPROPERTY() TArray<AXLagBuilding*> BuildingCollection;
};