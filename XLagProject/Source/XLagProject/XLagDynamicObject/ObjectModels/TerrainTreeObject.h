#pragma once
#include "TerrainObjectBase.h"

UENUM()
enum TreeParameterId
{
	ParId_TreeKind = CommonParameterId::ParId_UserDefined + 0,
	ParId_TreeAge = CommonParameterId::ParId_UserDefined + 1,
	ParId_TreeState = CommonParameterId::ParId_UserDefined + 2,
	ParId_TreeSustainability = CommonParameterId::ParId_UserDefined + 3,
	ParId_Broach = CommonParameterId::ParId_UserDefined + 4,
};

enum TreeState
{
	Growing,
	Falling,
	Fallen,
	IsTimber
};

struct TerrainTreeObject : public TerrainObjectBase
{
	TerrainTreeObject(FXLagObjectProperties& properties) : TerrainObjectBase(properties)
	{
	}

	XLagProperty(Age, int8, ParId_TreeAge)
	XLagProperty(Kind, int8, ParId_TreeKind)
	XLagProperty(TreeState, int8, ParId_TreeState)
	XLagProperty(TreeSustainability, float, ParId_TreeSustainability)
	XLagProperty(TreeBroach, float, ParId_Broach)
};