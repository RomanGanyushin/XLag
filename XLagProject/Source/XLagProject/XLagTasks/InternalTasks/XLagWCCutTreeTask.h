#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWoodCutter.h"

class XLagWCCutTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCCutTreeTask(FXLagDynamicTerrainMapItem& cell)
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
			UE_LOG(LogTemp, Error, TEXT("XLagWCCutTreeTask::Execute "));
		}

		auto isFinished = woodcutter->CutTree(Cell, DeltaTime);

		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }

	FXLagDynamicTerrainMapItem& Cell;
};
