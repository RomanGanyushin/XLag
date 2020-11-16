#pragma once

#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWoodCutter.h"
#include "../../XLagNPC/XLagTimberStack.h"

/*
Задача для дровосека - положтиь дерево (бревно).
*/
class XLagWCPutTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCPutTreeTask(AXLagTimberStack* stack)
		: Stack(stack)
	{

	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		Stack->AddTimber();
		Completed = true;
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }

	AXLagTimberStack *Stack;
};
