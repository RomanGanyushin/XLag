#pragma once
#include "../Common/XLagObjectProperties.h"
#include "XLagDynamicObject.generated.h"

UENUM(BlueprintType)
enum XLagDynamicObjectType
{
	Tree_,
	Crop_
};

USTRUCT(BlueprintType)
struct FXLagDynamicObject : public  FXLagObjectProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
		int32 Id = 0;

	/// ��� �������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
		TEnumAsByte<XLagDynamicObjectType> ObjectType;

	/// ��������� ������.
	UPROPERTY(SaveGame)
		TArray<uint32> BindedMapItemIndexes;
};