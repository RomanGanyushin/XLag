#include "XLagProductionSchemasManager.h"

AXLagProductionSchemasManager::AXLagProductionSchemasManager()
{

}

void AXLagProductionSchemasManager::CompliteCreate()
{
	auto element_id = 1;
	for (auto& it : ProductionSchemaCollection)
	{
		it.ID = element_id++;
	}
}

const bool AXLagProductionSchemasManager::IsNameOfProduct(const FString& name) const
{
	return ProductionSchemaCollection.ContainsByPredicate([&name](auto& i) {return i.Name == name; });
}

const FXLagProductionSchema& AXLagProductionSchemasManager::FindByName(const FString& name) const
{
	return *ProductionSchemaCollection.FindByPredicate([&name](auto& i) {return i.Name == name; });
}

const FXLagProductionSchema& AXLagProductionSchemasManager::FindById(const int32 id) const
{
	return *ProductionSchemaCollection.FindByPredicate([&id](auto& i) {return i.ID == id; });
}