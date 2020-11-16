#pragma once
#include "../Common/XLagObjectProperties.h"
#include "XLagDynamicObject.generated.h"

UENUM(BlueprintType)
enum XLagDynamicObjectType
{
	Tree_,
	Crop_
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPropertyChangedDelegate, uint8, id, const FXLagObjectProperties&, properties);

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

	// ������� ����������� ��� ��������� ��������.
	UPROPERTY(BlueprintAssignable)
		FPropertyChangedDelegate PropertyChangedEvent;

	void SetValue(uint8 id, const FVariant& value) override
	{
		FXLagObjectProperties::SetValue(id, value);
		PropertyChangedEvent.Broadcast(id, *this);
	}
};