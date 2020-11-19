#pragma once
#include "TerrainObjectBase.h"

UENUM()
enum CropParameterId
{
	ParId_CropKind = CommonParameterId::ParId_UserDefined + 0,
	ParId_CropLifeTime = CommonParameterId::ParId_UserDefined + 1,
	ParId_CropEvalution = CommonParameterId::ParId_UserDefined + 2,
	ParId_CropQuantity = CommonParameterId::ParId_UserDefined + 3,
};

struct TerrainCropObject : public TerrainObjectBase
{
	TerrainCropObject(FXLagObjectProperties& properties) : TerrainObjectBase(properties)
	{
	}

	XLagProperty(Kind, int8, ParId_CropKind);
	XLagProperty(Lifetime, float, ParId_CropLifeTime);
	XLagProperty(Evalution, float, ParId_CropEvalution);
	XLagProperty(CropQuantity, float, ParId_CropEvalution);
};