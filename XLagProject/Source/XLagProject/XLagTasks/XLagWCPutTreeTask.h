#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "../XLagNPC/XLagCuttableTreeBase.h"
#include "../XLagNPC/XLagNPCWoodCutter.h"
#include "../XLagNPC/XLagTimberStack.h"

/*
������ ��� ��������� - ����� ������ (������).
*/
class XLagWCPutTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCPutTreeTask(AXLagCuttableTreeBase* tree, AXLagTimberStack* stack)
		:Tree(tree), Stack(stack)
	{

	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		Stack->AddTimber(Tree);
		Completed = true;
	}

	virtual bool IsSuccess() override { return Completed; }

	AXLagCuttableTreeBase* Tree;
	AXLagTimberStack *Stack;

	bool Completed = false;
};
