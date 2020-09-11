#pragma once

#include "../XLagSelect/XLagSelectComponent.h"
#include "../XLagNPC/XLagNPCBase.h"
#include "../Common/ProfessionTypeEnum.h"
#include "XLagNPCTaskBase.h"
#include "XLagTaskManager.generated.h"

UENUM()
enum GroundAlignType
{
	Diging,
	Pouring,
	Smoothing
};

UENUM(BlueprintType)
enum TaskStateEnum
{
	Created UMETA(DisplayName = "Created"),
	WaitForBegin UMETA(DisplayName = "WaitForBeging"),
	InProgess UMETA(DisplayName = "InProgess"),
	Done UMETA(DisplayName = "Done")
};



UCLASS()
class UXLagTaskBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly) TEnumAsByte<ProfessionTypeEnum> ProfessionType;
	UPROPERTY(BlueprintReadOnly) FString TaskTypeName;	
	UPROPERTY(BlueprintReadOnly) int MaximalExecuterCount;
	UPROPERTY(BlueprintReadOnly) int MinimalExecuterCount;
	UPROPERTY(BlueprintReadOnly) TArray<AXLagNPCBase*> Executers;
	UPROPERTY(BlueprintReadOnly) TEnumAsByte<TaskStateEnum> State;
	UPROPERTY(BlueprintReadOnly) AXLagSelectComponent *Select;

public:
	std::shared_ptr<XLagNPCTaskBase> NpcTask;
};

UCLASS()
class UXLagTask_CreateGroundAlign: public UXLagTaskBase
{
	GENERATED_BODY()
		UXLagTask_CreateGroundAlign()
	{
		ProfessionType = ProfessionTypeEnum::Builder;
		TaskTypeName = TEXT("GroundAlignTask");
		MaximalExecuterCount = 2;
		MinimalExecuterCount = 1;
		State = TaskStateEnum::Created;
	}

public:
	void SetAlignRegion(std::shared_ptr<ITerrainMapAccessor> region)
	{
		Region = region;
	}
private:
	std::shared_ptr<ITerrainMapAccessor> Region;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPerformersSearchDelegate, AXLagTaskManager*, manager, UXLagTaskBase*, task);

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

	// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable) void CreateGroundAlignTask(AXLagSelectComponent *select, GroundAlignType type, float zParameter);
	UFUNCTION(BlueprintCallable) void ApplyForTask(AXLagNPCBase *npc, UXLagTaskBase* task);

	UPROPERTY() TArray<UXLagTaskBase*> Tasks;

	// —обытие возникающее при поиске исполните€ задачи.
	UPROPERTY(BlueprintAssignable, Category = "Tasks Collection Events")
		FPerformersSearchDelegate PerformersSearchEvent;

private:
	// «апросы от исполнителей.
	TMap<UXLagTaskBase*, TArray<AXLagNPCBase*>> _requestForExecution;

private:
	void SearchAndChooseExecuters(UXLagTaskBase* task);

};