#include "XLagProductionSchemasManager.h"

AXLagProductionSchemasManager::AXLagProductionSchemasManager()
{

}

const bool AXLagProductionSchemasManager::IsNameOfProduct(const FString& name) const
{
	return ProductionSchemaCollection.ContainsByPredicate([&name](auto& i) {return i.Name == name; });
}

const FXLagProductionSchema* AXLagProductionSchemasManager::SearchByName(const FString& name) const
{
	return ProductionSchemaCollection.FindByPredicate([&name](auto& i) {return i.Name == name; });
}