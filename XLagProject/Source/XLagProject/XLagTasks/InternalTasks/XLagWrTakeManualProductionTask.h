#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWorker.h"

class XLagWrTakeManualProductionTask : public XLagNPCTaskBase
{
public:
	XLagWrTakeManualProductionTask(std::string productName, float quanity)
		:_productName(productName), _quanity (quanity)
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

		if (worker->ManualProduction(FString(_productName.c_str()), _quanity, DeltaTime))
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
	const std::string _productName;
	const float _quanity;
};