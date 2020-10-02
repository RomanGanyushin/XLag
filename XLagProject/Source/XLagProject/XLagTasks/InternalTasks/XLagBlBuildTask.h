#pragma once

#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCBuilderman.h"
#include "../../XLagBuildings/XLagBuilding.h"

class XLagBlBuildTask : public XLagNPCTaskBase
{
public:
	XLagBlBuildTask(AXLagBuilding* building)
		:_building(building)
	{
	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		_building->Build();
	}

	virtual bool IsSuccess() override { return Completed; }
	bool Completed = false;
private:
	AXLagBuilding* _building;
};