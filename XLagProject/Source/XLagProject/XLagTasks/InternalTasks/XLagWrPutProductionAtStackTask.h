#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWorker.h"
#include "../../XLagNPC/XLagProductStack.h"

class XLagWrPutProductionAtStackTask : public XLagNPCTaskBase
{
public:
	XLagWrPutProductionAtStackTask(const int32 productId)
		:_productId(productId)
	{
	
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto worker = dynamic_cast<AXLagNPCWorker*>(npc);
		if (worker == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagWrPutProductionAtStackTask::Execute npc not Worker"));
			return;
		}

		if (worker->PutProductAtStack(_productId, DeltaTime))
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
};