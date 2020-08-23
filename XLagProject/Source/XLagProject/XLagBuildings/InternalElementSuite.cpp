#include "InternalElementSuite.h"


UMaterial* AInternalElementSuite::GetMaterial(const FString& name)
{
	return BuildingMaterials.FindRef(name);
}

UStaticMesh* AInternalElementSuite::GetTemplate(const FString& name)
{
	return BuildingElements.FindRef(name);
}