#pragma once

#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWoodCutter.h"

/*
Задача для дровосека - положтиь дерево (бревно).
*/
class XLagWCPutTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCPutTreeTask()
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto woodcutter = dynamic_cast<AXLagNPCWoodCutter*>(npc);
		if (woodcutter == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("XLagWCPutTreeTask::Execute "));
		}

		if (!woodcutter->Baggage->HasObject(XLagDynamicObjectType::Tree))
		{
			Completed = true;
			return;
		}

		if (woodcutter->FindCellIndex == -1)
		{
			Completed = true;
			return;
		}

		Completed = woodcutter->PutTreeToStack(DeltaTime);
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
};
