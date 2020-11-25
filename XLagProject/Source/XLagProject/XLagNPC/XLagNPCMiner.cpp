// Fill out your copyright notice in the Description page of Project Settings.
#include "XLagNPCMiner.h"
#include "../BuildDefinition.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"
#include "../Common/CellOperationProcessing.h"
#include "../XLagDynamicObject/ObjectModels/TerrainLooseStackObject.h"
#include "../XLagDynamicTerrainBase.h"
#include "../XLagDynamicTerrain\Position\RandomizeZeroPlacePosition.h"

void AXLagNPCMiner::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}

bool AXLagNPCMiner::SearchMineral(FXLagDynamicTerrainMapItem& cell, const int mineralId, float DeltaTime)
{
	auto searchForce = DeltaTime;
	auto& mineral = AXLagMineralManager::GetMineralManager()->FindById(mineralId);

	auto searchComplexity = mineral.SearchComplexity;

	auto isComplite = XLagDynamicTerrainMapItemOperation(cell).CheckForMineral(mineral.ID);
	if (!isComplite)
	{
		CellOperationProcessing operation(&cell, CellOperationEnum::SearchMineral, searchComplexity);
		operation.Increase(searchForce);
		
		if (operation.IsComplete())
		{
			isComplite = true;
			cell.CreateMineralLayerEventRaise(&cell, mineral);
		}	
	}

	IsSearching = !isComplite;

	return isComplite;
}

bool AXLagNPCMiner::ExtractMineral(FXLagDynamicTerrainMapItem& cell, const int mineralId, float DeltaTime)
{
	auto& mineral = AXLagMineralManager::GetMineralManager()->FindById(mineralId);

	auto force = DeltaTime;
	auto extractingForce = force * DEBUG_FORCE_MULTIPLIER;
	auto extractedQuantity = XLagDynamicTerrainMapItemOperation(cell).ExtractResource(mineral, extractingForce);
  	if (extractedQuantity == 0.0f)
	{
		IsExtracting = false;
		return true;
	}

	Baggage->Put(XLagDynamicObjectType::Mineral, mineralId, extractedQuantity); //TODO_ONE Подставить название 
	auto isComplite = Baggage->HasQuanity(XLagDynamicObjectType::Mineral, mineralId, 10.0f); // Вынести в статы.

	IsExtracting = !isComplite;
	return isComplite; 
}

// Найди стопку.
bool AXLagNPCMiner::SearchStack(int32 mineralId)
{
	auto& objects = AXLagDynamicObjectsManager::GetManagment()->GetObjects();
	auto mineralStacks = objects.GetFilteredByType(XLagDynamicObjectType::MineralStack);

	auto searchCondition = [mineralId](auto it)
	{
		TerrainMineralStackObject stackProperties(*it);
		return stackProperties.GetKind() == mineralId;
	};

	auto searchingStack = mineralStacks.FindByPredicate(searchCondition);

	if (searchingStack == nullptr) // Если стопки нет, то создаем.
	{
		auto terrain = AXLagDynamicTerrainBase::GetDynamicTerrainBase();
		auto cell = RandomizeZeroPlacePosition(terrain->Map).GetCell();

		FXLagDynamicObject stackObject;
		stackObject.ObjectType = XLagDynamicObjectType::MineralStack;
		stackObject.BindedMapItemIndexes.Add(cell->Index);

		TerrainMineralStackObject stackProperties(stackObject);
		stackProperties.SetKind(mineralId);
		objects.AddObject(stackObject);

		FindCellIndex = cell->Index;
	}
	else
	{
		FindCellIndex = (*searchingStack)->BindedMapItemIndexes[0];
	}

	return true;
}

bool AXLagNPCMiner::PutMineralToStack(float DeltaTime)
{
	auto quantity = DeltaTime;

	auto terrain = AXLagDynamicTerrainBase::GetDynamicTerrainBase();
	auto& cell = terrain->Map->Point(FindCellIndex);

	XLagDynamicTerrainMapItemOperation cellOperation(cell);
	if (!cellOperation.HasObjectType(XLagDynamicObjectType::MineralStack))
	{
		IsDischarging = false;
		return true;
	}

	auto object = cellOperation.GetObjectByType(XLagDynamicObjectType::MineralStack);
	TerrainMineralStackObject mineralStackObjectProperty(*object);
	auto mineralId = mineralStackObjectProperty.GetKind();

	auto getFromBaggageMineralQuantity = Baggage->Take(XLagDynamicObjectType::Mineral, mineralId, quantity); //TODO_ONE Подставить название 

	if (getFromBaggageMineralQuantity == 0.0f)
	{

		IsDischarging = false;
		return true;
	}

	mineralStackObjectProperty.SetStackQuantity(mineralStackObjectProperty.GetStackQuantity() + getFromBaggageMineralQuantity);

	IsDischarging = true;
	return false;
}