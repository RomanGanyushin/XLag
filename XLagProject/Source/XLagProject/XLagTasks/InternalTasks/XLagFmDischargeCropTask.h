#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCFarmer.h"
#include "../../XLagNPC/XLagCropStack.h"

class XLagFmDischargeCropTask : public XLagNPCTaskBase
{
public:
	XLagFmDischargeCropTask(AXLagCropStack* stack)
		:_stack(stack)
	{
	}

	void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto farmer = dynamic_cast<AXLagNPCFarmer*>(npc);
		if (farmer == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagMiDischargeMineralTask::Execute npc not Farmer"));
			return;
		}

		_stack->AddQuantity(farmer->CollectedCropQuantity);
		farmer->CollectedCropQuantity = 0.0f;
		Completed = true;
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
	bool Completed = false;

private:
	AXLagCropStack* _stack;
};