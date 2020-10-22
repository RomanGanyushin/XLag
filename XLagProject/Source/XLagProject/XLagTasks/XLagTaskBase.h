#pragma once

#include "TaskStateEnum.h"
#include "../XLagSelect/XLagSelectComponent.h"
#include "InternalTasks/XLagNPCTaskBase.h"
#include "InternalTasks/XLagNPCTaskContext.h"
#include "../XLagNPC/XLagNPCBase.h"
#include "../Common/ProfessionTypeEnum.h"
#include "XLagTaskBase.generated.h"

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
	XLagNPCTaskContext TaskContext;
public:
	bool CheckForNpcRequire();
	bool CheckForAwait();
private:
	std::shared_ptr<XLagNPCTaskBase> GetCurrentSubTask();
};