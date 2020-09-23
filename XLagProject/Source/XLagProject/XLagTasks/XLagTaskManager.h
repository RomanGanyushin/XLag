#pragma once

#include "XLagTaskBase.h"
#include "../Common/GroundAlignTypeEnum.h"
#include "../XLagMinerals/Models/XLagMineralDesc.h"

#include "XLagTaskManager.generated.h"


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

	// ������� ������ ������������.
	UFUNCTION(BlueprintCallable) void CreateGroundAlignTask(AXLagSelectComponent *select, GroundAlignTypeEnum type, TerrainElementEnum pourElement, float zParameter, int RequiredWorkerNumber);

	// ������� ������ �������.
	UFUNCTION(BlueprintCallable) void CreateCuttingTreeTask(AXLagSelectComponent *select, AXLagTimberStack *timberStack, int RequiredWorkerNumber);

	// ������� ������ ������ �������� ����������.
	UFUNCTION(BlueprintCallable) void CreateSearchMineralTask(AXLagSelectComponent *select, const FXLagMineralDesc mineral, int RequiredWorkerNumber);

	// ������� ������ ������ �������� ����������.
	UFUNCTION(BlueprintCallable) void CreateExtractMineralTask(AXLagSelectComponent *select, const FXLagMineralDesc mineral, int RequiredWorkerNumber);
	
	// ������ �� ���������� ������ �� ������� npc.
	UFUNCTION(BlueprintCallable) void ApplyForTask(AXLagNPCBase *npc, UXLagTaskBase* task);

	// ������.
	UPROPERTY() TArray<UXLagTaskBase*> Tasks;

	// ������� ����������� ��� ������ ���������� ������.
	UPROPERTY(BlueprintAssignable, Category = "Tasks Collection Events")
		FPerformersSearchDelegate PerformersSearchEvent;

private:
	// ������� �� ������������.
	TMap<UXLagTaskBase*, TArray<AXLagNPCBase*>> _requestForExecution;

private:
	void SearchAndChooseExecuters();
	void SearchAndChooseExecuters(UXLagTaskBase* task);

};