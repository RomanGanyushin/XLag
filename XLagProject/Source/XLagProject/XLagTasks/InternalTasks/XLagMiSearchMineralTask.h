#pragma once


#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCMiner.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagMinerals/Models/XLagMineralDesc.h"

class XLagMiSearchMineralTask : public XLagNPCTaskBase
{
public:
	XLagMiSearchMineralTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, const FXLagMineralDesc mineral)
		:Map(map), X(x), Y(y), Mineral(mineral)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto miner = dynamic_cast<AXLagNPCMiner*>(npc);
		if (miner == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagMiSearchMineralTask::Execute npc not Miner"));
			return;
		}

		auto& mapCell = Map->Point(X, Y);
		auto isFinished = miner->SearchMineral(mapCell, Mineral, DeltaTime);

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
	const FXLagMineralDesc Mineral;
};
