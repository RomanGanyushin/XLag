#include "XLagDynamicObjects.h"
#include <algorithm>

void FXLagDynamicObjects::AddObject(TEnumAsByte<XLagDynamicObjectType> objectType, const uint32 mapItemIndex, const FXLagObjectProperties properties)
{
	FXLagDynamicObject newObject;
	newObject.ObjectType = objectType;
	newObject.BindedMapItemIndexes.Add(mapItemIndex);
	newObject.SetProperties(properties);
	AddObject(newObject);
}

void FXLagDynamicObjects::AddObject(const FXLagDynamicObject& object)
{
	auto newIndex = Objects.Add(object);	
	AddObjectEvent.Broadcast(newIndex);
}

void FXLagDynamicObjects::RemoveObject(FXLagDynamicObject* object)
{
	auto removeIndex = Objects.IndexOfByPredicate([object](auto& it) {return &it == object; });
	RemovingObjectEvent.Broadcast(removeIndex);
	Objects.RemoveAt(removeIndex);
}

FXLagDynamicObject* FXLagDynamicObjects::FindById(int32 id)
{
	return Objects.FindByPredicate([id](auto& it) {return it.Id == id; });
}

TArray<FXLagDynamicObject*> FXLagDynamicObjects::GetFilteredByType(TEnumAsByte<XLagDynamicObjectType> objectType)
{
	TArray<FXLagDynamicObject*> filteredObjects;

	for (auto& it : Objects)
	{
		if (it.ObjectType == objectType)
		{
			filteredObjects.Add(&it);
		}
	}

	return filteredObjects;
}

void FXLagDynamicObjects::RaiseAddNewObjectsEvent()
{
	for (int index = 0; index < Objects.Num(); index++)
	{
		AddObjectEvent.Broadcast(index);
	}
}