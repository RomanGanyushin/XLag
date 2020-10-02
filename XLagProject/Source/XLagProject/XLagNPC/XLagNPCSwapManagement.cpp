// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagNPCSwapManagement.h"
#include "../XLagDynamicTerrain/Position/RandomizeZeroPlacePosition.h"
#include "../XLagDynamicTerrain/Filters/SurfaceResourceMapItemFilter.h"

// Sets default values
AXLagNPCSwapManagement::AXLagNPCSwapManagement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AXLagNPCSwapManagement::BeginPlay()
{
	Super::BeginPlay();
}

void AXLagNPCSwapManagement::DoSwapPersons()
{
	if (WoodcutterTemplate != nullptr)
	{
		for (int i = 0; i < StartWoodcuterCount; i++)
		{
			auto locator = RandomizeZeroPlacePosition(MapAccessor).Get() + FVector(0, 0, 200);
			auto woodcutter = GetWorld()->SpawnActor<AXLagNPCWoodCutter>(WoodcutterTemplate, locator, FRotator::ZeroRotator);

			if (woodcutter == nullptr)
				continue;

			auto scaleVector = CalculatePersonScale(WoodcuterDeviationHeightPercent, WoodcuterDeviationThicknessPercent);
			woodcutter->SetActorScale3D(scaleVector);

			//Test_AttachTask_CutTrees(woodcutter, i);
		}	
	}

	if (BuilderTemplate != nullptr)
	{
		for (int i = 0; i < StartBuilderCount; i++)
		{
			auto locator = RandomizeZeroPlacePosition(MapAccessor).Get() + FVector(0, 0, 200);
			auto builder = GetWorld()->SpawnActor<AXLagNPCBuilderman>(BuilderTemplate, locator, FRotator::ZeroRotator);

			if (builder == nullptr)
				continue;

			auto scaleVector = CalculatePersonScale(BuilderDeviationHeightPercent, BuilderDeviationThicknessPercent);
			builder->SetActorScale3D(scaleVector);
		}
	}

	if (MinerTemplate != nullptr)
	{
		for (int i = 0; i < StartMinerCount; i++)
		{
			auto locator = RandomizeZeroPlacePosition(MapAccessor).Get() + FVector(0, 0, 200);
			auto miner = GetWorld()->SpawnActor<AXLagNPCMiner>(MinerTemplate, locator, FRotator::ZeroRotator);

			if (miner == nullptr)
				continue;

			auto scaleVector = CalculatePersonScale(MinerDeviationHeightPercent, MinerDeviationThicknessPercent);
			miner->SetActorScale3D(scaleVector);	
		}
	}

	if (OperationSelectionTemplate != nullptr)
	{
		auto selection = GetWorld()->SpawnActor<AXLagSelectComponent>(OperationSelectionTemplate, FVector::ZeroVector, FRotator::ZeroRotator);
		selection->Init(MapAccessor);
	}

	///DoSwapBuilding();
}

AXLagBuilding* AXLagNPCSwapManagement::DoSwapBuilding()
{
	if (BuildingTemplate == nullptr)
		return nullptr;

	return GetWorld()->SpawnActor<AXLagBuilding>(BuildingTemplate, FVector(5000 + 100, 5000 + 100, 0), FRotator::ZeroRotator);
}

void AXLagNPCSwapManagement::DoSwapTrees()
{
	if (TreeTemplates.Num() == 0)
		return;

	auto mapRequireTrees = MapAccessor->GetFilteredItems(SurfaceResourceMapItemFilter(OnSurfaceResourceObjectsEnum::Tree));
	if (mapRequireTrees.empty())
		return;

	for (int i = 0; i < std::min((int)mapRequireTrees.size(), MaximalCount); i++)
	{
		auto treeTemplate = TreeTemplates[i % TreeTemplates.Num()];
		if (treeTemplate == nullptr)
			continue;

		auto mapItem = mapRequireTrees[i];
		auto loction = MapAccessor->GetWorldPosition(mapItem, GetPositionEnum::CenterLowPosition);
		auto rotator = FRotator(0, rand() % 360 , 0);

		auto tree = GetWorld()->SpawnActor<AXLagCuttableTreeBase>(treeTemplate, loction, rotator);
		tree->UpdateAge(MinimalAge + rand() % int(MaximalAge - MinimalAge));
		tree->SetPlaceId(mapItem->GetId());

		SwapedTrees.Add(tree);
	}	
}

void AXLagNPCSwapManagement::DoSwapTreeStack()
{
	auto locator = RandomizeZeroPlacePosition(MapAccessor).Get();
	auto stack = GetWorld()->SpawnActor<AXLagTimberStack>(TimberStackTemplate, locator, FRotator::ZeroRotator);
	SwapedTreeStacks.Add(stack);
}

AXLagMineralStack* AXLagNPCSwapManagement::DoSwapMineralStack(const FXLagMineralDesc& mineral)
{
	auto locator = RandomizeZeroPlacePosition(MapAccessor).Get();
	auto stack = GetWorld()->SpawnActor<AXLagMineralStack>(MineralStackTemplate, locator, FRotator::ZeroRotator);
	stack->Initialize(mineral, 2, 2);
	SwapedMineralStacks.Add(stack);
	return stack;
}

// Called every frame
void AXLagNPCSwapManagement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AXLagNPCSwapManagement::CalculatePersonScale(int deviationHeightPercent, int deviationThicknessPercent)
{
	float scale_xy = 1.f + ((float)(rand() % deviationThicknessPercent) - deviationThicknessPercent / 2) / 100.f;
	float scale_z = 1.f + ((float)(rand() % deviationHeightPercent) - deviationHeightPercent / 2) / 100.f;
	return FVector(scale_xy, scale_xy, scale_z);
}

