#include "InternalElementSuite.h"


UMaterial* AInternalElementSuite::GetMaterial(const FString& name, bool preview)
{
	auto suite = BuildingMaterials.Find(name);
	if (suite == nullptr)
		return nullptr;

	return preview ? suite->PreviewMateria : suite->NormalMaterial;
}

UStaticMesh* AInternalElementSuite::GetTemplate(const FString& name, bool preview)
{
	auto suite = BuildingElements.Find(name);
	if (suite == nullptr)
		return nullptr;

	return preview ? suite->PreviewElement : suite->NormalElement;
}