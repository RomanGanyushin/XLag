#pragma once

#include "XLagDynamicObject.h"
#include "XLagDynamicObjects.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddObjectDelegate, const int32, newIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemovingObjectDelegate, const int32, removingIndex);

USTRUCT(BlueprintType)
struct FXLagDynamicObjects
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TArray<FXLagDynamicObject> Objects;

	void RaiseAddNewObjectsEvent();
	
	FAddObjectDelegate AddObjectEvent;
	FRemovingObjectDelegate RemovingObjectEvent;

	void AddObject(TEnumAsByte<XLagDynamicObjectType> objectType, const uint32 mapItemIndex, const FXLagObjectProperties properties);
	void AddObject(const FXLagDynamicObject& object);
	void RemoveObject(FXLagDynamicObject* object);

	FXLagDynamicObject* FindById(int32 id);
	TArray<FXLagDynamicObject*> GetFilteredByType(TEnumAsByte<XLagDynamicObjectType> objectType);
};
