// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XLagNPCWoodCutter.h"
#include "XLagNPCBuilderman.h"
#include "XLagNPCMiner.h"
#include "XLagCuttableTreeBase.h"
#include "XLagTimberStack.h"
#include "XLagMineralStack.h"
#include "../XLagSelect/XLagSelectComponent.h"
#include "../XLagBuildings/XLagBuilding.h"
#include "../Common/ITerrainMapAccessor.h"
#include "XLagNPCSwapManagement.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagNPCSwapManagement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXLagNPCSwapManagement();
	
	inline static AXLagNPCSwapManagement* GetManagment()
	{
		AXLagNPCSwapManagement *currentObject = nullptr;
		
		for (TObjectIterator<AXLagNPCSwapManagement> It; It; ++It)
		{
			currentObject = *It;
		}

		return currentObject;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetMapAccessor(std::shared_ptr<ITerrainMapAccessor> accessor) { MapAccessor = accessor; }
	void DoSwapPersons();
	void DoSwapTrees();
	void DoSwapTreeStack();
	AXLagMineralStack* DoSwapMineralStack(const FXLagMineralDesc& mineral);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
 
// �������� ��������� - ���������.
public:
	// ������ ���������.
	UPROPERTY(EditAnywhere, Category = "Spawn Woodcutter Params")
		TSubclassOf<AXLagNPCWoodCutter> WoodcutterTemplate;

	// ���������� ���������� �� ������ ����. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Woodcutter Params")
	int StartWoodcuterCount = 5;

	// ��������� �������� ����� (������� �� ����������� �����).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Woodcutter Params")
	int WoodcuterDeviationHeightPercent = 30;

	// ��������� �������� ������� (������� �� ����������� �����).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Woodcutter Params")
	int WoodcuterDeviationThicknessPercent = 10;

// �������� ��������� - ���������.
public:
	// ������ ���������.
	UPROPERTY(EditAnywhere, Category = "Spawn Builder Params")
		TSubclassOf<AXLagNPCBuilderman> BuilderTemplate;

	// ���������� ���������� �� ������ ����. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Builder Params")
		int StartBuilderCount = 2;

	// ��������� �������� ����� (������� �� ����������� �����).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Builder Params")
		int BuilderDeviationHeightPercent = 30;

	// ��������� �������� ������� (������� �� ����������� �����).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Builder Params")
		int BuilderDeviationThicknessPercent = 10;

// �������� ��������� - �������.
public:
	// ������ ���������.
	UPROPERTY(EditAnywhere, Category = "Spawn Miner Params")
		TSubclassOf<AXLagNPCMiner> MinerTemplate;

	// ���������� ���������� �� ������ ����. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Miner Params")
		int StartMinerCount = 2;

	// ��������� �������� ����� (������� �� ����������� �����).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Miner Params")
		int MinerDeviationHeightPercent = 30;

	// ��������� �������� ������� (������� �� ����������� �����).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Miner Params")
		int MinerDeviationThicknessPercent = 10;

// �������� ������� ��������
public:

	// ������� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Trees Params")
		TArray<TSubclassOf<AXLagCuttableTreeBase>> TreeTemplates;

	// ����������� �������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Trees Params")
	float MinimalAge = 20;

	// ������������ �������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Trees Params")
	float MaximalAge = 100;

	// ������������ ���������� �������� ��� �������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Trees Params")
	int MaximalCount = 50;

public:

	// ������ ������� ������.
	UPROPERTY(EditAnywhere, Category = "Timber Stack Params")
		TSubclassOf<AXLagTimberStack> TimberStackTemplate;

	// ������ ������� ������.
	UPROPERTY(EditAnywhere, Category = "Mineral Stack Params")
		TSubclassOf<AXLagMineralStack> MineralStackTemplate;
	
	// ������ ��������� �������
	UPROPERTY(EditAnywhere, Category = "Selection Params")
		TSubclassOf<AXLagSelectComponent> OperationSelectionTemplate;

	// ������ ������.
	UPROPERTY(EditAnywhere, Category = "Building Params")
		TSubclassOf<AXLagBuilding> BuildingTemplate;
	
private:
	std::shared_ptr<ITerrainMapAccessor> MapAccessor;

public:
	TArray<AXLagCuttableTreeBase*> SwapedTrees;
	TArray<AXLagTimberStack*> SwapedTreeStacks;
	TArray<AXLagMineralStack*> SwapedMineralStacks;
	
private:
	FVector CalculatePersonScale(int deviationHeightPercent, int deviationThicknessPercent);

	// �������� ��� �����.
private:
	void Test_AttachTask_CutTrees(AXLagNPCWoodCutter *woodcutter, int index);
	void Test_AttachTask_Dig(AXLagNPCBuilderman *builder, int index);
};
