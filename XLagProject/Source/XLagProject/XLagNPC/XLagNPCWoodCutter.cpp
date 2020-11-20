// Fill out your copyright notice in the Description page of Project Settings.
#include "XLagNPCWoodCutter.h"
#include "../XLagDynamicObject/ObjectModels/TerrainTreeObject.h"
#include "../XLagDynamicObject/ObjectModels/TerrainTimberStackObject.h"
#include "../XLagDynamicTerrainBase.h"
#include "../XLagDynamicTerrain\Position\RandomizeZeroPlacePosition.h"

void AXLagNPCWoodCutter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AXLagNPCWoodCutter::CutTree(FXLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto isComplite = false;
	auto cutTreeForce = DeltaTime;
	XLagDynamicTerrainMapItemOperation cellOperation(cell);

	if (!cellOperation.HasObjectType(XLagDynamicObjectType::Timber))
	{
		IsCutting = false;
		return true;
	}

	auto treeObject = cellOperation.GetObjectByType(XLagDynamicObjectType::Timber);
	TerrainTreeObject treeProperties(*treeObject);

	auto currentSustainability = treeProperties.GetTreeSustainability();
	auto newSustainability = std::max(0.0f, currentSustainability - cutTreeForce);
	treeProperties.SetTreeSustainability(newSustainability);
	isComplite = newSustainability == 0.0f;

	IsCutting = !isComplite;

	return isComplite;
}

bool AXLagNPCWoodCutter::BroachTree(FXLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto isComplite = false;
	auto broachTreeForce = DeltaTime;
	XLagDynamicTerrainMapItemOperation cellOperation(cell);

	if (!cellOperation.HasObjectType(XLagDynamicObjectType::Timber))
	{
		IsBroaching = false;
		return true;
	}

	auto treeObject = cellOperation.GetObjectByType(XLagDynamicObjectType::Timber);
	TerrainTreeObject treeProperties(*treeObject);

	auto currentBroach = treeProperties.GetTreeBroach();
	auto newBroach = std::min(100.0f, currentBroach + broachTreeForce);
	treeProperties.SetTreeBroach(newBroach);

	isComplite = treeProperties.GetTreeState() == TreeState::IsTimber;

	IsBroaching = !isComplite;

	return isComplite;
}

bool AXLagNPCWoodCutter::GetTree(FXLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	XLagDynamicTerrainMapItemOperation cellOperation(cell);

	if (!cellOperation.HasObjectType(XLagDynamicObjectType::Timber))
	{
		return true;
	}

	auto treeObject = cellOperation.GetObjectByType(XLagDynamicObjectType::Timber);
	cellOperation.DeleteObject(treeObject);

	Baggage->Put(XLagDynamicObjectType::Timber, "Tree", 1);

	return true;
}

bool AXLagNPCWoodCutter::SearchStack()
{
	auto& objects = AXLagDynamicObjectsManager::GetManagment()->GetObjects();
	auto timberStacks = objects.GetFilteredByType(XLagDynamicObjectType::TimberStack);

	if (timberStacks.Num() == 0) // Если стопки нет, то создаем.
	{
		auto terrain = AXLagDynamicTerrainBase::GetDynamicTerrainBase();
		auto cell = RandomizeZeroPlacePosition(terrain->Map).GetCell();

		FXLagDynamicObject stackObject;
		stackObject.ObjectType = XLagDynamicObjectType::TimberStack;
		stackObject.BindedMapItemIndexes.Add(cell->Index);

		TerrainTimberStackObject stackProperties(stackObject);
		objects.AddObject(stackObject);

		FindCellIndex = cell->Index;
	}
	else
	{
		auto stack = timberStacks[0];
		FindCellIndex = stack->BindedMapItemIndexes[0];
	}

	return true;
}

bool AXLagNPCWoodCutter::PutTreeToStack(float DeltaTime)
{
	auto terrain = AXLagDynamicTerrainBase::GetDynamicTerrainBase();
	auto& cell = terrain->Map->Point(FindCellIndex);

	XLagDynamicTerrainMapItemOperation cellOperation(cell);
	if (!cellOperation.HasObjectType(XLagDynamicObjectType::TimberStack))
		return true;

	auto object = cellOperation.GetObjectByType(XLagDynamicObjectType::TimberStack);
	TerrainTimberStackObject timberStackObjectProperty(*object);
	timberStackObjectProperty.SetTimberQuantity(timberStackObjectProperty.GetTimberQuantity() + 1);
	Baggage->Reset(XLagDynamicObjectType::Timber);

	return true;
}

void AXLagNPCWoodCutter::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}
