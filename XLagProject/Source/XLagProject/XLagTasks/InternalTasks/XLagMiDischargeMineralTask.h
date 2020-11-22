#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCMiner.h"
#include "../../XLagNPC/XLagMineralStack.h"

class XLagMiDischargeMineralTask : public XLagNPCTaskBase
{
public:
	XLagMiDischargeMineralTask()
	{
	}

	void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto miner = dynamic_cast<AXLagNPCMiner*>(npc);
		if (miner == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagMiDischargeMineralTask::Execute npc not Miner"));
			return;
		}

		if (!miner->Baggage->HasObject(XLagDynamicObjectType::Mineral))
		{
			Completed = true;
			return;
		}

		if (miner->FindCellIndex == -1)
		{
			Completed = true;
			return;
		}

		Completed = miner->PutMineralToStack(DeltaTime);
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
};
