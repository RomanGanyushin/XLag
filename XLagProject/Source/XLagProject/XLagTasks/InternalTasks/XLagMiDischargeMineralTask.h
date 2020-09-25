#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCMiner.h"
#include "../../XLagNPC/XLagMineralStack.h"

class XLagMiDischargeMineralTask : public XLagNPCTaskBase
{
public:
	XLagMiDischargeMineralTask(AXLagMineralStack* stack)
		:_stack(stack)
	{
	}

	void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		auto miner = dynamic_cast<AXLagNPCMiner*>(npc);
		if (miner == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagMiDischargeMineralTask::Execute npc not Miner"));
			return;
		}

		_stack->AddMineral(miner->ExtractedMineralQuantity);
		miner->ExtractedMineralQuantity = 0.0f;
		Completed = true;
	}

	virtual bool IsSuccess() override { return Completed; }
	bool Completed = false;

private:		
	AXLagMineralStack* _stack;
};
