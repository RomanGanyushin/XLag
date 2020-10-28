#pragma once
#include "Models/XLagProductionSchema.h"
#include "XLagProductionSchemasManager.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagProductionSchemasManager : public AActor
{
	GENERATED_BODY()
public:
	AXLagProductionSchemasManager();

	inline static AXLagProductionSchemasManager* GetManagment()
	{
		AXLagProductionSchemasManager *currentObject = nullptr;

		for (TObjectIterator<AXLagProductionSchemasManager> It; It; ++It)
		{
			currentObject = *It;
		}

		return currentObject;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collection")
		TArray<FXLagProductionSchema> ProductionSchemaCollection;
};