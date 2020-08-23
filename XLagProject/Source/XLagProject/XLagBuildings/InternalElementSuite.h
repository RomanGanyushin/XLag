#pragma once

#include "InternalElementSuite.generated.h"

UCLASS(Blueprintable)
class AInternalElementSuite : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elements Materials")
	TMap<FString, UMaterial*> BuildingMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elements Template")
	TMap<FString, UStaticMesh*> BuildingElements;

	virtual UMaterial* GetMaterial(const FString& name);
	virtual UStaticMesh* GetTemplate(const FString& name);

public:
	static AInternalElementSuite* GetSuite()
	{
		for (TObjectIterator<AInternalElementSuite> It; It; ++It)
		{
			AInternalElementSuite* CurrentObject = (AInternalElementSuite*)*It;
			return (AInternalElementSuite *)CurrentObject;
		}

		return nullptr;
	}
};