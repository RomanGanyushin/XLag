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

TArray<AXLagMineralStack*> AXLagMineralManager::FindMineralStackFor(const FString& name)
{
	auto swapManagement = AXLagNPCSwapManagement::GetManagment();
	auto searchConditionFunc = [&name](auto i) { return i->ContentMineral.Name == name; };
	auto mineralStacksByName = swapManagement->SwapedMineralStacks.FilterByPredicate(searchConditionFunc);
	return mineralStacksByName;
}

TArray<AXLagMineralStack*> AXLagMineralManager::FindReserveredMineralStackFor(const AXLagNPCBase* npc)
{
	auto swapManagement = AXLagNPCSwapManagement::GetManagment();
	auto searchConditionFunc = [npc](auto i) { return i->IsReservedFor(npc); };
	auto mineralStacksByName = swapManagement->SwapedMineralStacks.FilterByPredicate(searchConditionFunc);
	return mineralStacksByName;
}