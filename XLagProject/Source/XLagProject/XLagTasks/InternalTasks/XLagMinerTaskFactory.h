#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "../../XLagDynamicTerrain\Position/MinMaxLevelPlace.h"
#include "../../Common/ITerrainMapAccessor.h"

/*
 Фабрика задач для шахтера.
*/
class XLagMinerTaskFactory
{
public:
	float CompliteDistanceToTree = 1.0f;
	float SpaceScale = 100.f;

public:
	XLagMinerTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
		: Place(place)
	{
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};