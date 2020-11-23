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

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto builder = dynamic_cast<AXLagNPCBuilderman*>(npc);
		if (builder == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagBlBuildTask::Execute npc not Builder"));
			return;
		}

		builder->Build(_building);
		Completed = _building->IsBuildComplited;

		if (Completed)
		{
			//builder->Cancel();
		}		
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
	bool Completed = false;
private:
	AXLagBuilding* _building;
};