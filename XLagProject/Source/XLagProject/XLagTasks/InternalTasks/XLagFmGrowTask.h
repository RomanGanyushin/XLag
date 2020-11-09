#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCFarmer.h"
#include "../../Common/ITerrainMapAccessor.h"

class XLagFmGrowTask : public XLagNPCTaskBase
{
public:
	XLagFmGrowTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y)
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
			UE_LOG(LogTemp, Log, TEXT("XLagFmCultivateTask::Execute npc not Farmer"));
			return;
		}

		auto& mapCell = Map->Point(X, Y);

		auto isFinished = farmer->Grow(mapCell, DeltaTime);
		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
	

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;
};