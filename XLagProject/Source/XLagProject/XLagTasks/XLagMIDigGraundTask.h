#pragma once

#include "XLagNPCTaskBase.h"
#include "../XLagNPC/XLagNPCMiner.h"
#include "../Common/ITerrainMapAccessor.h"

class XLagMIDigGraundTask : public XLagNPCTaskBase
{
public:
	XLagMIDigGraundTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, float level) 
		:Map(map), X(x), Y(y), Level(level)
	{
#ifdef ENABLE_TASK_LOG
		UE_LOG(LogTemp, Log, TEXT("XLagMIDigGraundTask"));
#endif
	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		auto miner = dynamic_cast<AXLagNPCMiner*>(npc);
		if (miner == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagMIDigGraundTask::Execute npc not Miner"));
			return;
		}

		XLagDynamicTerrainMapItem& mapCell = Map->Point(X, Y);
		miner->Dig(mapCell, Level);

		if (mapCell.GetTopLevel() - Level <= 1)
		{
			Completed = true;
			UE_LOG(LogTemp, Log, TEXT("XLagMIDigGraundTask::Execute  Completed !!!!"));
		}
	}

	virtual bool IsSuccess() override { return Completed; }
	bool Completed = false;

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;
	float Level;
};
