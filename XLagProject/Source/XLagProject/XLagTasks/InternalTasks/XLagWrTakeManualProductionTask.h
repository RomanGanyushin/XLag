#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWorker.h"

class XLagWrTakeManualProductionTask : public XLagNPCTaskBase
{
public:
	XLagWrTakeManualProductionTask(const int32 productId, float quanity)
		:_productId(productId), _quanity (quanity)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto worker = dynamic_cast<AXLagNPCWorker*>(npc);
		if (worker == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagWrTakeManualProductionTask::Execute npc not Worker"));
			return;
		}

		if (worker->ManualProduction(_productId, _quanity, DeltaTime))
		{
			Completed = true;
			return;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return Completed;
	}

private:
	const int32 _productId;
	const float _quanity;
};