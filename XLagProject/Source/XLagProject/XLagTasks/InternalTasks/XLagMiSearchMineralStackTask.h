#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCMiner.h"

/*
Задача для фермера - найти (или создать) стопку для урожая.
*/
class XLagMiSearchMineralStackTask : public XLagNPCTaskBase
{
public:
	XLagMiSearchMineralStackTask(const int32 mineralId)
		: MineralId(mineralId)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto miner = dynamic_cast<AXLagNPCMiner*>(npc);
		if (miner == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("XLagMiSearchMineralStackTask::Execute "));
		}

		auto isFinished = miner->SearchStack(MineralId);
		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }

private:
	int32 MineralId;
};