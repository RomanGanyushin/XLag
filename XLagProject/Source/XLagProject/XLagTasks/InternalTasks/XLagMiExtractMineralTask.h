#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCMiner.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagMinerals/Models/XLagMineralDesc.h"

class XLagMiExtractMineralTask : public XLagNPCTaskBase
{
public:
	XLagMiExtractMineralTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, const int mineralId)
		:Map(map), X(x), Y(y), MineralId(mineralId)
	{
	}

	void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto miner = dynamic_cast<AXLagNPCMiner*>(npc);
		if (miner == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagMiExtractMineralTask::Execute npc not Miner"));
			return;
		}

		auto& mapCell = Map->Point(X, Y);
		auto isFinished = miner->ExtractMineral(mapCell, MineralId, DeltaTime);

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
	const int32 MineralId;
};
