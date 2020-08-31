#pragma once

#include "../XLagSelect/XLagSelectComponent.h"
#include "XLagTaskManager.generated.h"

UENUM()
enum GroundAlignType
{
	Diging,
	Pouring,
	Smoothing
};

UENUM()
enum ProfessionType
{
	Builder,
	Miner,
	Treecutter
};

UCLASS()
class UXLagTaskBase : public UObject
{
	GENERATED_BODY()

public:
	FString TaskTypeName;
	ProfessionType ProfessionType;
};

UCLASS()
class UXLagTask_CreateGroundAlign: public UXLagTaskBase
{
	GENERATED_BODY()
};


UCLASS()
class XLAGPROJECT_API AXLagTaskManager : public AActor
{
	GENERATED_BODY()

public:
	AXLagTaskManager();
	UFUNCTION(BlueprintCallable) void CreateGroundAlignTask(AXLagSelectComponent *select, GroundAlignType type, float zParameter);
	UPROPERTY() TArray<TSubclassOf<UXLagTaskBase>> Tasks;
};