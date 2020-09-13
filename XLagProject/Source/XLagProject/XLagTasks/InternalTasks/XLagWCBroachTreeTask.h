#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "../../XLagNPC/XLagCuttableTreeBase.h"
#include "../../XLagNPC/XLagNPCWoodCutter.h"

/*
Задача для дровосека - обтесать дерево до бревна.
*/
class XLagWCBroachTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCBroachTreeTask(AXLagCuttableTreeBase* tree)
		:Tree(tree)
	{

	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		auto woodcutter = dynamic_cast<AXLagNPCWoodCutter*>(npc);
		if (woodcutter == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("XLagWCBroachTreeTask::Execute "));
		}

		if (Tree->IsTimber())
		{
			woodcutter->Cancel();
			Completed = true;
			return;
		}

		if (!Tree->CanBroach())
		{
			return;
		}

		if (!Tree->IsTimber())
		{
			if (!woodcutter->IsBroaching)
			{
				woodcutter->BeginBroachTree(Tree);
			}		
		}
	}

	virtual bool IsSuccess() override { return Completed; }

	AXLagCuttableTreeBase* Tree;
	bool Completed = false;
};
