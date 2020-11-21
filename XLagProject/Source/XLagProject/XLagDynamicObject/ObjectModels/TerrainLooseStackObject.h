#pragma once
#include "TerrainObjectBase.h"

UENUM()
enum LooseStackParameterId
{
	ParId_StackKind = CommonParameterId::ParId_UserDefined + 0,
	ParId_StackQuantity = CommonParameterId::ParId_UserDefined + 1,
	ParId_StackInheredDefined = CommonParameterId::ParId_UserDefined + 2
};

//UENUM()
//enum CropStackParameterId
//{
//};


struct TerrainLooseStackObject : public TerrainObjectBase
{
	TerrainLooseStackObject(FXLagObjectProperties& properties) : TerrainObjectBase(properties)
	{
	}

	XLagProperty(Kind, int16, ParId_StackKind);
	XLagProperty(StackQuantity, float, ParId_StackQuantity);
};

struct TerrainCropStackObject : public TerrainLooseStackObject
{
	TerrainCropStackObject(FXLagObjectProperties& properties) : TerrainLooseStackObject(properties)
	{
	}
};

struct TerrainMineralStackObject : public TerrainLooseStackObject
{
	TerrainMineralStackObject(FXLagObjectProperties& properties) : TerrainLooseStackObject(properties)
	{
	}
};