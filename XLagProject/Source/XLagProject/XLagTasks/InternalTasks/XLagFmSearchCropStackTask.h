#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCFarmer.h"

/*
Задача для фермера - найти (или создать) стопку для урожая.
*/
class XLagFmSearchCropStackTask : public XLagNPCTaskBase
{
public:
	XLagFmSearchCropStackTask(const int32 cropId) 
		: CropId(cropId)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto farmer = dynamic_cast<AXLagNPCFarmer*>(npc);
		if (farmer == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("XLagWCSearchCropStackTask::Execute "));
		}

		auto isFinished = farmer->SearchStack(CropId);
		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }

private:
	int32 CropId;
};