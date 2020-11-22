#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWorker.h"
#include "../../XLagNPC/XLagProductStack.h"

/*
Задача для фермера - найти (или создать) стопку для урожая.
*/
class XLagWrSearchProductStackTask : public XLagNPCTaskBase
{
public:
	XLagWrSearchProductStackTask(const int32 productId)
		: _productId(productId)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto worker = dynamic_cast<AXLagNPCWorker*>(npc);
		if (worker == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagMiSearchMineralStackTask::Execute npc not Worker"));
			return;
		}

		auto isFinished = worker->SearchProductStack(_productId);
		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }

private:
	const int32 _productId;
};