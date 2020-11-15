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

	void SetKind(const int8 type)
	{
		Properties.SetValue(ParId_CropKind, type);
	}

	const int8 GetKind()
	{
		return Properties.GetValue<int8>(ParId_CropKind);
	}

	void SetLifetime(const float type)
	{
		Properties.SetValue(ParId_CropLifeTime, type);
	}

	const float GetLifetime()
	{
		return Properties.GetValue<float>(ParId_CropLifeTime);
	}

	void SetEvalution(const float type)
	{
		Properties.SetValue(ParId_CropEvalution, type);
	}

	const float GetEvalution()
	{
		return Properties.GetValue<float>(ParId_CropEvalution);
	}

	void SetCropQuantity(const float type)
	{
		Properties.SetValue(ParId_CropQuantity, type);
	}

	const float GetCropQuantity()
	{
		return Properties.GetValue<float>(ParId_CropQuantity);
	}
};