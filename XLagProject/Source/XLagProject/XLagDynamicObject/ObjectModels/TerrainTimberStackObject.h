#pragma once
#include "TerrainObjectBase.h"

UENUM()
enum TimberStackParameterId
{
	ParId_TimberStackQuantity = CommonParameterId::ParId_UserDefined + 0,
};

struct TerrainTimberStackObject : public TerrainObjectBase
{
	TerrainTimberStackObject(FXLagObjectProperties& properties) : TerrainObjectBase(properties)
	{
	}

	XLagProperty(TreeQuantity, float, ParId_TimberStackQuantity);
};