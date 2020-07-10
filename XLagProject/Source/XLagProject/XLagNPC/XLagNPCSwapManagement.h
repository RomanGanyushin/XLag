// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XLagNPCWoodCutter.h"
#include "XLagCuttableTreeBase.h"
#include "XLagTimberStack.h"
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
	void SetMapAccessor(ITerrainMapAccessor *accessor) { MapAccessor = accessor; }
	void DoSwapPersons();
	void DoSwapTrees();
	void DoSwapTreeStack();

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

	// Шаблон дровосека.
	UPROPERTY(EditAnywhere, Category = "Timber Stack Params")
	TSubclassOf<AXLagTimberStack> TimberStackTemplate;
	

private:
	ITerrainMapAccessor* MapAccessor;
	TArray<AXLagCuttableTreeBase*> SwapedTrees;
	TArray<AXLagTimberStack*> SwapedTreeStacks;
private:
	FVector CalculatePersonScale(int deviationHeightPercent, int deviationThicknessPercent);

};
