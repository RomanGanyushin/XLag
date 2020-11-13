#include "XLagDynamicObjects.h"

void FXLagDynamicObjects::AddObject(TEnumAsByte<LagDynamicObjectType> objectType, const uint32 mapItemIndex, const FXLagObjectProperties properties)
{
	FXLagDynamicObject newObject;
	newObject.ObjectType = objectType;
	newObject.BindedMapItemIndexes.Add(mapItemIndex);
	newObject.SetProperties(properties);

	Objects.Add(newObject);
	AddObjectEvent.Broadcast(newObject);
}