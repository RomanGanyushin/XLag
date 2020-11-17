// Fill out your copyright notice in the Description page of Project Settings.
#include "XLagNPCWoodCutter.h"
#include "../XLagDynamicObject/ObjectModels/TerrainTreeObject.h"

void AXLagNPCWoodCutter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AXLagNPCWoodCutter::CutTree(FXLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto isComplite = false;
	auto cutTreeForce = DeltaTime;
	XLagDynamicTerrainMapItemOperation cellOperation(cell);

	if (!cellOperation.HasObjectType(XLagDynamicObjectType::Tree))
	{
		IsCutting = false;
		return true;
	}

	auto treeObject = cellOperation.GetObjectByType(XLagDynamicObjectType::Tree);
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

	if (!cellOperation.HasObjectType(XLagDynamicObjectType::Tree))
	{
		IsBroaching = false;
		return true;
	}

	auto treeObject = cellOperation.GetObjectByType(XLagDynamicObjectType::Tree);
	TerrainTreeObject treeProperties(*treeObject);

	auto currentBroach = treeProperties.GetTreeBroach();
	auto newBroach = std::min(100.0f, currentBroach + broachTreeForce);
	treeProperties.SetTreeBroach(newBroach);

	isComplite = treeProperties.GetTreeState() == TreeState::Timber;

	IsBroaching = !isComplite;

	return isComplite;
}

bool AXLagNPCWoodCutter::GetTree(FXLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	XLagDynamicTerrainMapItemOperation cellOperation(cell);

	if (!cellOperation.HasObjectType(XLagDynamicObjectType::Tree))
	{
		return true;
	}

	auto treeObject = cellOperation.GetObjectByType(XLagDynamicObjectType::Tree);
	cellOperation.DeleteObject(treeObject);

	Baggage->Put(XLagDynamicObjectType::Tree, "Tree", 1);

	return true;
}

void AXLagNPCWoodCutter::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}
