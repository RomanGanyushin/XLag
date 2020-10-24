#pragma once
#include "XLagNPCTaskBase.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagNPC/XLagNPCFarmer.h"

class XLagFmCropTakeTask : public XLagNPCTaskBase
{
public:
	XLagFmCropTakeTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y)
		:Map(map), X(x), Y(y)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto farmer = dynamic_cast<AXLagNPCFarmer*>(npc);
		if (farmer == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagFmCropTask::Execute npc not Farmer"));
			return;
		}

		auto& mapCell = Map->Point(X, Y);
		auto isFinished = farmer->TakeCrop(mapCell, DeltaTime);

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
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;
};