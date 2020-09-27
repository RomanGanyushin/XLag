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
 
// Свойства персонажа - дровосека.
public:
	// Шаблон дровосека.
	UPROPERTY(EditAnywhere, Category = "Spawn Woodcutter Params")
		TSubclassOf<AXLagNPCWoodCutter> WoodcutterTemplate;

	// Количество дровосеков на старте игры. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Woodcutter Params")
	int StartWoodcuterCount = 5;

	// Амплитуда разброса роста (процент от норамльного роста).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Woodcutter Params")
	int WoodcuterDeviationHeightPercent = 30;

	// Амплитуда разброма толщины (процент от норамльного роста).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Woodcutter Params")
	int WoodcuterDeviationThicknessPercent = 10;

// Свойства персонажа - строителя.
public:
	// Шаблон дровосека.
	UPROPERTY(EditAnywhere, Category = "Spawn Builder Params")
		TSubclassOf<AXLagNPCBuilderman> BuilderTemplate;

	// Количество дровосеков на старте игры. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Builder Params")
		int StartBuilderCount = 2;

	// Амплитуда разброса роста (процент от норамльного роста).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Builder Params")
		int BuilderDeviationHeightPercent = 30;

	// Амплитуда разброма толщины (процент от норамльного роста).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Builder Params")
		int BuilderDeviationThicknessPercent = 10;

// Свойства персонажа - шахтера.
public:
	// Шаблон дровосека.
	UPROPERTY(EditAnywhere, Category = "Spawn Miner Params")
		TSubclassOf<AXLagNPCMiner> MinerTemplate;

	// Количество дровосеков на старте игры. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Miner Params")
		int StartMinerCount = 2;

	// Амплитуда разброса роста (процент от норамльного роста).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Miner Params")
		int MinerDeviationHeightPercent = 30;

	// Амплитуда разброма толщины (процент от норамльного роста).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Miner Params")
		int MinerDeviationThicknessPercent = 10;

// Свойства высадки деревьев
public:

	// Шаблоны дерева
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Trees Params")
		TArray<TSubclassOf<AXLagCuttableTreeBase>> TreeTemplates;

	// Минимальный возраст.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Trees Params")
	float MinimalAge = 20;

	// Максимальный возраст.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Trees Params")
	float MaximalAge = 100;

	// Максимальное количество деревьев для локации.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Trees Params")
	int MaximalCount = 50;

public:

	// Шаблон штабеля бревен.
	UPROPERTY(EditAnywhere, Category = "Timber Stack Params")
		TSubclassOf<AXLagTimberStack> TimberStackTemplate;

	// Шаблон штабеля бревен.
	UPROPERTY(EditAnywhere, Category = "Mineral Stack Params")
		TSubclassOf<AXLagMineralStack> MineralStackTemplate;
	
	// Шаблон выделения области
	UPROPERTY(EditAnywhere, Category = "Selection Params")
		TSubclassOf<AXLagSelectComponent> OperationSelectionTemplate;

	// Шаблон здания.
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

	// Временно для теста.
private:
	void Test_AttachTask_CutTrees(AXLagNPCWoodCutter *woodcutter, int index);
	void Test_AttachTask_Dig(AXLagNPCBuilderman *builder, int index);
};
