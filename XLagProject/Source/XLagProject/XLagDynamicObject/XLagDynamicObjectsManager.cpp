#include "XLagDynamicObjectsManager.h"
#include "ObjectModels/TerrainCropObjectBehavior.h"
#include "ObjectModels/TerrainTreeObjectBehavior.h"
#include "../XLagNPC/XLagNPCSwapManagement.h"

AXLagDynamicObjectsManager::AXLagDynamicObjectsManager()
{
	PrimaryActorTick.bCanEverTick = true;

	_behaviors.Add(XLagDynamicObjectType::Crop, std::shared_ptr<TerrainObjectBehaviorBase>(new TerrainCropObjectBehavior()));
	_behaviors.Add(XLagDynamicObjectType::Timber, std::shared_ptr<TerrainObjectBehaviorBase>(new TerrainTreeObjectBehavior()));
}

void AXLagDynamicObjectsManager::OnInitialze(AGameModeBase* gameMode)
{
	auto& terrainObjects = ((AXLagProjectGameMode*)gameMode)->TerrainObjects;
	auto& terrainMap = ((AXLagProjectGameMode*)gameMode)->TerrainMap;

	_terrainObjects = &terrainObjects;
	_terrainMap = &terrainMap;

	terrainObjects.AddObjectEvent.AddDynamic(this, &AXLagDynamicObjectsManager::OnAddNewObject);
	terrainObjects.RemovingObjectEvent.AddDynamic(this, &AXLagDynamicObjectsManager::OnRemovingObject);
}

void AXLagDynamicObjectsManager::OnAddNewObject(const int32 newIndex)
{
	auto& newObject = _terrainObjects->Objects[newIndex];

	static int32 staticIdCounter = 0;
	newObject.Id = staticIdCounter++;

	for (auto it : newObject.BindedMapItemIndexes)
	{	
		FXLagDynamicObjectRef ref;
		ref.ObjectId = newObject.Id;
		ref.ObjectType = newObject.ObjectType;

		_terrainMap->Map[it].RefItemObjects.Add(ref);
	}

	switch (newObject.ObjectType)
	{
		case XLagDynamicObjectType::Timber:
			AXLagNPCSwapManagement::GetManagment()->DoSwapTree(newObject);
			break;

		case XLagDynamicObjectType::Crop:
			AXLagNPCSwapManagement::GetManagment()->DoSwapCrop(newObject);
			break;

		case XLagDynamicObjectType::TimberStack:
			AXLagNPCSwapManagement::GetManagment()->DoSwapTreeStack(newObject);
			break;

		case XLagDynamicObjectType::CropStack:
			AXLagNPCSwapManagement::GetManagment()->DoSwapCropStack(newObject);
			break;
	}
}


void AXLagDynamicObjectsManager::OnRemovingObject(const int32 removingIndex)
{
	auto& removingObject = _terrainObjects->Objects[removingIndex];
	auto removingObjectId = removingObject.Id;

	for (auto it : removingObject.BindedMapItemIndexes)
	{
		auto& references = _terrainMap->Map[it].RefItemObjects;
		references.RemoveAll([removingObjectId](auto& it) {return it.ObjectId == removingObjectId; });
	}

	switch (removingObject.ObjectType)
	{
		case XLagDynamicObjectType::Timber:
		case XLagDynamicObjectType::Crop:
			AXLagNPCSwapManagement::GetManagment()->DoUnswapObject(removingObjectId);
			break;
	}
}

void AXLagDynamicObjectsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_terrainObjects == nullptr)
		return;

	for (auto&it : _terrainObjects->Objects)
	{
		auto objectType = it.ObjectType;
		if (_behaviors.Contains(objectType))
		{
			_behaviors[objectType]->OnTick(&it, DeltaTime);
		}
	}
}