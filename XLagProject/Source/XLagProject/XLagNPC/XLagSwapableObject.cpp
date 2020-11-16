#include "XLagSwapableObject.h"

AXLagSwapableObject::AXLagSwapableObject()
{
}

void AXLagSwapableObject::AssignObject(const FXLagDynamicObject& object)
{
	ObjectId = object.Id;
}