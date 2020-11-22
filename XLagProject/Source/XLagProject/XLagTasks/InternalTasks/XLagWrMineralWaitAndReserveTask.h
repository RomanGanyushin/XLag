#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWorker.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagMinerals/XLagMineralManager.h"

class XLagWrMineralWaitAndReserveTask : public XLagNPCTaskBase
{
public:
	XLagWrMineralWaitAndReserveTask(const int32 mineralId, float quanity)
		:MineralId(mineralId), _quanity(quanity)
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

		if (worker->Baggage->HasQuanity(XLagDynamicObjectType::Mineral, MineralId, _quanity))
		{
			Completed = true;
			return;
		}
		
		auto isFinished = worker->SearchAndReserveMineralStack(MineralId, _quanity);
		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return Completed;
	}

private:
	const int32 MineralId;
	const float _quanity;
};