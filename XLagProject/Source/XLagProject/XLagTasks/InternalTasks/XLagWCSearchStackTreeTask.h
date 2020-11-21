#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWoodCutter.h"

/*
Задача для дровосека - найти (или создать) стопку для бревен.
*/
class XLagWCSearchStackTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCSearchStackTreeTask()
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

		auto isFinished = woodcutter->SearchStack();
		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
};
