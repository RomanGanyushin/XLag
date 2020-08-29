#pragma once

#include "InternalElementSuite.generated.h"

USTRUCT(Blueprintable)
struct FMaterialSuite
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterial* NormalMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterial* PreviewMateria;
};

USTRUCT(Blueprintable)
struct FElementSuite
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UStaticMesh* NormalElement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UStaticMesh* PreviewElement;
};


UCLASS(Blueprintable)
class AInternalElementSuite : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elements Materials")
	TMap<FString, FMaterialSuite> BuildingMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elements Template")
	TMap<FString, FElementSuite> BuildingElements;

	virtual UMaterial* GetMaterial(const FString& name, bool preview = false);
	virtual UStaticMesh* GetTemplate(const FString& name, bool preview = false);

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