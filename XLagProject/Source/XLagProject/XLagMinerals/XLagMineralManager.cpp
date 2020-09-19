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

const TArray<FXLagMineralDesc> AXLagMineralManager::GetSearchableMeneralDescCollection() const 
{
	return MineralDescCollection.FilterByPredicate([](auto& i) {return i.SearchRequire; });
}