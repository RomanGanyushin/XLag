#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCFarmer.h"
#include "../../XLagNPC/XLagCropStack.h"

class XLagFmDischargeCropTask : public XLagNPCTaskBase
{
public:
	XLagFmDischargeCropTask()
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

		if (!farmer->Baggage->HasObject(XLagDynamicObjectType::Crop))
		{
			Completed = true;
			return;
		}

		if (farmer->FindCellIndex == -1)
		{
			Completed = true;
			return;
		}

		Completed = farmer->PutCropToStack(DeltaTime);
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
};