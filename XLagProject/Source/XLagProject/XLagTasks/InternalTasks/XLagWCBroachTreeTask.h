#pragma once

#include "XLagNPCTaskBase.h"
//#include "XLagNPCTaskMoveTo.h"
//#include "../../XLagNPC/XLagCuttableTreeBase.h"
#include "../../XLagNPC/XLagNPCWoodCutter.h"

/*
Задача для дровосека - обтесать дерево до бревна.
*/
class XLagWCBroachTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCBroachTreeTask(FXLagDynamicTerrainMapItem& cell)
		:Cell(cell)
	{

	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto woodcutter = dynamic_cast<AXLagNPCWoodCutter*>(npc);
		if (woodcutter == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("XLagWCBroachTreeTask::Execute "));
		}

		auto isFinished = woodcutter->BroachTree(Cell, DeltaTime);

		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }

	FXLagDynamicTerrainMapItem& Cell;
};
