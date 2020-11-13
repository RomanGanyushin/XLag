#pragma once

#include "XLagDynamicObject.h"
#include "XLagDynamicObjects.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddObjectDelegate, const FXLagDynamicObject&, object);

USTRUCT(BlueprintType)
struct FXLagDynamicObjects
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TArray<FXLagDynamicObject> Objects;

	// Событие возникающее добавление нового объекта.
	//UPROPERTY(BlueprintAssignable)
	FAddObjectDelegate AddObjectEvent;

	void AddObject(TEnumAsByte<LagDynamicObjectType> objectType, const uint32 mapItemIndex, const FXLagObjectProperties properties);
};