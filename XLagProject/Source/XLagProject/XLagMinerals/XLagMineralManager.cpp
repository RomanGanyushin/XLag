#include "XLagMineralManager.h"

AXLagMineralManager::AXLagMineralManager()
{
}

const TArray<FXLagMineralDesc> AXLagMineralManager::GetSearchableMeneralDescCollection() const 
{
	return MineralDescCollection.FilterByPredicate([](auto& i) {return i.SearchRequire; });
}