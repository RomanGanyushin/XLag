#pragma once
#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "../XLagNPC/XLagCuttableTreeBase.h"
#include "../XLagNPC/XLagNPCWoodCutter.h"

class XLagWCCutTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCCutTreeTask(AXLagCuttableTreeBase* tree)
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
			UE_LOG(LogTemp, Error, TEXT("XLagWCCutTreeTask::Execute "));
		}

		if (Tree->IsCutted())
		{
			Completed = true;
			woodcutter->Cancel();
		}
		else
		{
			if (!woodcutter->IsCutting)
			{
				woodcutter->BeginCutTree(Tree);
			}	
		}	
	}

	virtual bool IsSuccess() override { return Completed; }

	AXLagCuttableTreeBase* Tree;
	bool Completed = false;
};
