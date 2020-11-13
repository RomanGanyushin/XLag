#pragma once
#include "../../Common/XLagObjectProperties.h"
#include "TerrainObjectBase.generated.h"

UENUM()
enum CommonParameterId
{
	ParId_Location = 0,
	ParId_Rotation = 1,
};

USTRUCT(BlueprintType)
struct FTerrainObjectBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FXLagObjectProperties Properties;

	void SetLoction(const FVector& location)
	{
		Properties.SetValue(ParId_Location, location);
	}

	void SetRotaion(const FRotator& rotator)
	{
		Properties.SetValue(ParId_Rotation, rotator);
	}
};