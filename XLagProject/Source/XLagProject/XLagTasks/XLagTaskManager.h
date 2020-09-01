#pragma once

#include "../XLagSelect/XLagSelectComponent.h"
#include "../XLagNPC/XLagNPCBase.h"
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

	UPROPERTY(BlueprintReadOnly) TArray<AXLagNPCBase*> Executers;
	UPROPERTY(BlueprintReadOnly) AXLagSelectComponent *Select;
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

	inline static AXLagTaskManager* GetTaskManager()
	{
		AXLagTaskManager *currentObject = nullptr;

		for (TObjectIterator<AXLagTaskManager> It; It; ++It)
		{
			currentObject = *It;
		}

		return currentObject;
	}

	UFUNCTION(BlueprintCallable) void CreateGroundAlignTask(AXLagSelectComponent *select, GroundAlignType type, float zParameter);
	UFUNCTION(BlueprintCallable) void TakeTask(UXLagTaskBase* task, AXLagNPCBase *npc);
	UPROPERTY() TArray<UXLagTaskBase*> Tasks;
};