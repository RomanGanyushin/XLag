// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagNPCSwapManagement.h"
#include "../XLagDynamicTerrain/Position/RandomizeZeroPlacePosition.h"
#include "../XLagDynamicTerrain/Filters/SurfaceResourceMapItemFilter.h"
#include "../XLagDynamicObject/ObjectModels/TerrainTreeObject.h"
#include "../XLagDynamicObject/ObjectModels/TerrainCropObject.h"

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

	if (FarmerTemplate != nullptr)
	{
		for (int i = 0; i < StartFarmerCount; i++)
		{
			auto locator = RandomizeZeroPlacePosition(MapAccessor).Get() + FVector(0, 0, 200);
			auto farmer = GetWorld()->SpawnActor<AXLagNPCFarmer>(FarmerTemplate, locator, FRotator::ZeroRotator);

			if (farmer == nullptr)
				continue;

			auto scaleVector = CalculatePersonScale(FarmerDeviationHeightPercent, FarmerDeviationThicknessPercent);
			farmer->SetActorScale3D(scaleVector);
		}
	}

	if (WorkerTemplate != nullptr)
	{
		for (int i = 0; i < StartWorkerCount; i++)
		{
			auto locator = RandomizeZeroPlacePosition(MapAccessor).Get() + FVector(0, 0, 200);
			auto worker = GetWorld()->SpawnActor<AXLagNPCWorker>(WorkerTemplate, locator, FRotator::ZeroRotator);

			if (worker == nullptr)
				continue;

			auto scaleVector = CalculatePersonScale(WorkerDeviationHeightPercent, WorkerDeviationThicknessPercent);
			worker->SetActorScale3D(scaleVector);
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

void AXLagNPCSwapManagement::DoSwapTree(const FXLagDynamicObject& object)
{
	auto treeObject = TerrainTreeObject(const_cast<FXLagDynamicObject&>(object));

	auto loction = treeObject.GetLocation();
	auto rotator = treeObject.GetRotation();
	auto kind = treeObject.GetKind() % TreeTemplates.Num();
	auto age = treeObject.GetAge();

	auto treeTemplate = TreeTemplates[kind];

	auto tree = GetWorld()->SpawnActor<AXLagCuttableTreeBase>(treeTemplate, loction, rotator);
	tree->UpdateAge(age);
	tree->SetObject(const_cast<FXLagDynamicObject*>(&object));

	SwapedTrees.Add(tree);
}

void AXLagNPCSwapManagement::DoSwapCrop(const FXLagDynamicObject& object)
{
	auto cropObject = TerrainCropObject(const_cast<FXLagDynamicObject&>(object));

	if (!cropObject.HasLocation())
	{
		cropObject.SetLocation(MapAccessor->GetWorldPosition(object.BindedMapItemIndexes[0], GetPositionEnum::CenterHeghtPosition));
	}

	if (!cropObject.HasRotation())
	{
		cropObject.SetRotation(FRotator::ZeroRotator);
	}

	auto loction = cropObject.GetLocation();
	auto rotator = cropObject.GetRotation();
	auto cropId = cropObject.GetKind();

	auto cropManager = AXLagCropManager::GetCropsManager();
	auto cropDescription = cropManager->FindById(cropId);

	auto newCrop = GetWorld()->SpawnActor<AXLagCrop>(CropTemplate, loction, rotator);
	newCrop->Initialize(const_cast<FXLagDynamicObject*>(&object), cropDescription);
	SwapedCrops.Add(newCrop);
}

void AXLagNPCSwapManagement::DoUnswapCrop(const int32 objectId) //TODO: Сделать общую функцию для всех.
{
	auto unswapingIndex = SwapedCrops.IndexOfByPredicate([objectId](auto& it) {return it->GetAssingedObject()->Id == objectId; });
	GetWorld()->DestroyActor(SwapedCrops[unswapingIndex]);
	SwapedCrops.RemoveAt(unswapingIndex);
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

AXLagCropStack* AXLagNPCSwapManagement::DoSwapCropStack(const FXLagCropDescription& crop)
{
	auto locator = RandomizeZeroPlacePosition(MapAccessor).Get();
	auto stack = GetWorld()->SpawnActor<AXLagCropStack>(CropStackTemplate, locator, FRotator::ZeroRotator);
	stack->Initialize(crop, 2, 2);
	SwapedCropStacks.Add(stack);
	return stack;
}

AXLagProductStack* AXLagNPCSwapManagement::DoSwapProductStack(const FXLagProductionSchema& product)
{
	auto locator = RandomizeZeroPlacePosition(MapAccessor).Get();
	auto stack = GetWorld()->SpawnActor<AXLagProductStack>(ProductStackTemplate, locator, FRotator::ZeroRotator);
	stack->ProductPresentMesh = product.ProductPresentation;
	SwapedProductStacks.Add(stack);
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

