#include "XLagMineralManager.h"

AXLagMineralManager::AXLagMineralManager()
{
}

void AXLagMineralManager::CompliteCreate()
{
	auto element_id = 1;
	for (auto& it : MineralDescCollection)
	{
		it.ID = element_id++;
	}
}

const bool AXLagMineralManager::Empty() const
{
	return MineralDescCollection.Num() == 0;
}

const TArray<FXLagMineralDesc> AXLagMineralManager::GetSearchableMineralDescCollection() const 
{
	return MineralDescCollection.FilterByPredicate([](auto& i) {return i.SearchRequire; });
}

const TArray<FXLagMineralDesc> AXLagMineralManager::GetTerrainMineralDescCollection() const
{
	return MineralDescCollection.FilterByPredicate([](auto& i) {return i.MineralTerrainElement != TerrainElementEnum::None; });
}