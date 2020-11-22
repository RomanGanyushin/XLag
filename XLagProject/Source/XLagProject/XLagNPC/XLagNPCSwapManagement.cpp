// Fill out your copyright notice in the Description page of Project Settings.
#include "XLagNPCSwapManagement.h"
#include "../XLagDynamicTerrain/Position/RandomizeZeroPlacePosition.h"
#include "../XLagDynamicTerrain/Filters/SurfaceResourceMapItemFilter.h"
#include "../XLagDynamicObject/ObjectModels/TerrainTreeObject.h"
#include "../XLagDynamicObject/ObjectModels/TerrainCropObject.h"
#include "../XLagDynamicObject/ObjectModels/TerrainTimberStackObject.h"
#include "../XLagDynamicObject/ObjectModels/TerrainLooseStackObject.h"

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
			woodcutter->DefaultInitialize();

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
			builder->DefaultInitialize();

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
			miner->DefaultInitialize();

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
			farmer->DefaultInitialize();

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
			worker->DefaultInitialize();

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
	tree->AssignObject(object);
	tree->UpdateAge(age);
	 
	SwapedObjects.Add(tree);
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
	newCrop->AssignObject(object);
	newCrop->Initialize(cropDescription);

	SwapedObjects.Add(newCrop);
}

void AXLagNPCSwapManagement::DoSwapTreeStack(const FXLagDynamicObject& object)
{
	auto treeStackObject = TerrainTimberStackObject(const_cast<FXLagDynamicObject&>(object));

	if (!treeStackObject.HasLocation())
	{
		treeStackObject.SetLocation(MapAccessor->GetWorldPosition(object.BindedMapItemIndexes[0], GetPositionEnum::CenterHeghtPosition));
	}

	if (!treeStackObject.HasRotation())
	{
		treeStackObject.SetRotation(FRotator::ZeroRotator);
	}

	auto loction = treeStackObject.GetLocation();
	auto rotator = treeStackObject.GetRotation();

	auto stack = GetWorld()->SpawnActor<AXLagTimberStack>(TimberStackTemplate, loction, rotator);
	stack->AssignObject(object);

	SwapedObjects.Add(stack);
}

void AXLagNPCSwapManagement::DoSwapCropStack(const FXLagDynamicObject& object)
{
	auto cropStackObject = TerrainCropStackObject(const_cast<FXLagDynamicObject&>(object));

	if (!cropStackObject.HasLocation())
	{
		cropStackObject.SetLocation(MapAccessor->GetWorldPosition(object.BindedMapItemIndexes[0], GetPositionEnum::CenterHeghtPosition));
	}

	if (!cropStackObject.HasRotation())
	{
		cropStackObject.SetRotation(FRotator::ZeroRotator);
	}

	auto loction = cropStackObject.GetLocation();
	auto rotator = cropStackObject.GetRotation();
	auto cropId = cropStackObject.GetKind();

	auto cropManager = AXLagCropManager::GetCropsManager();
	auto cropDescription = cropManager->FindById(cropId);

	auto stack = GetWorld()->SpawnActor<AXLagCropStack>(CropStackTemplate, loction, rotator);
	stack->AssignObject(object);
	stack->Initialize(cropDescription, 2, 2);
	SwapedObjects.Add(stack);
}

void AXLagNPCSwapManagement::DoSwapMineralStack(const FXLagDynamicObject& object)
{
	auto mineralStackObject = TerrainMineralStackObject(const_cast<FXLagDynamicObject&>(object));

	if (!mineralStackObject.HasLocation())
	{
		mineralStackObject.SetLocation(MapAccessor->GetWorldPosition(object.BindedMapItemIndexes[0], GetPositionEnum::CenterHeghtPosition));
	}

	if (!mineralStackObject.HasRotation())
	{
		mineralStackObject.SetRotation(FRotator::ZeroRotator);
	}

	auto loction = mineralStackObject.GetLocation();
	auto rotator = mineralStackObject.GetRotation();
	auto mineralId = mineralStackObject.GetKind();

	auto mineralManager = AXLagMineralManager::GetMineralManager();
	auto mineral = mineralManager->FindById(mineralId);

	auto stack = GetWorld()->SpawnActor<AXLagMineralStack>(MineralStackTemplate, loction, rotator);
	stack->AssignObject(object);
	stack->Initialize(mineral, 2, 2);
	SwapedObjects.Add(stack);
}

void AXLagNPCSwapManagement::DoUnswapObject(const int32 objectId)
{
	auto unswapingIndex = SwapedObjects.IndexOfByPredicate([objectId](auto& it) {return it->ObjectId == objectId; });
	GetWorld()->DestroyActor(SwapedObjects[unswapingIndex]);
	SwapedObjects.RemoveAt(unswapingIndex);
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

