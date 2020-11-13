#include "XLagDynamicObjectsManager.h"

AXLagDynamicObjectsManager::AXLagDynamicObjectsManager()
{
}

void AXLagDynamicObjectsManager::OnInitialze(AGameModeBase* gameMode)
{
	auto& terrainMap = ((AXLagProjectGameMode*)gameMode)->TerrainMap;
	auto& terrainObjects = ((AXLagProjectGameMode*)gameMode)->TerrainObjects;

	terrainObjects.AddObjectEvent.AddDynamic(this, &AXLagDynamicObjectsManager::OnAddNewObject);
}

void AXLagDynamicObjectsManager::OnAddNewObject(const FXLagDynamicObject& object)
{

}