#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWorker.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagMinerals/XLagMineralManager.h"

class XLagWrTakeReservedMineralsTask : public XLagNPCTaskBase
{
public:
	XLagWrTakeReservedMineralsTask(const float quantity)
		: _quantity(quantity)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto worker = dynamic_cast<AXLagNPCWorker*>(npc);
		if (worker == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagWrMineralWaitTask::Execute npc not Worker"));
			return;
		}

		Completed = worker->TakeReservedMineral(DeltaTime, _quantity);
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return Completed;
	}

private:
	const float _quantity;
};