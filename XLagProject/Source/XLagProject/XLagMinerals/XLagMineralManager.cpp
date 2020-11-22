#include "XLagMineralManager.h"
#include "../XLagNPC/XLagNPCSwapManagement.h"

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

const bool AXLagMineralManager::IsNameOfMineral(const FString& name) const
{
	return MineralDescCollection.ContainsByPredicate([&name](auto& i) {return i.Name == name; });
}

const FXLagMineralDesc* AXLagMineralManager::SearchByName(const FString& name) const
{
	return MineralDescCollection.FindByPredicate([&name](auto& i) {return i.Name == name; });
}

const FXLagMineralDesc& AXLagMineralManager::FindById(const int32 id) const
{
	return *MineralDescCollection.FindByPredicate([id](auto& it) {return it.ID == id; });
}
