#pragma once

#include "XLagNPCTaskBase.h"
#include "../XLagNPC/XLagNPCMiner.h"
#include "../Common/ITerrainMapAccessor.h"

class XLagMIPourGraundTask : public XLagNPCTaskBase
{
public:
	XLagMIPourGraundTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, float level, TerrainElementEnum element)
		:Map(map), X(x), Y(y), Level(level), Element(element)
	{
#ifdef ENABLE_TASK_LOG
		UE_LOG(LogTemp, Log, TEXT("XLagMIPourGraundTask"));
#endif
	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		auto miner = dynamic_cast<AXLagNPCMiner*>(npc);
		if (miner == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagMIPourGraundTask::Execute npc not Miner"));
			return;
		}

		XLagDynamicTerrainMapItem& mapCell = Map->Point(X, Y);
		miner->Pour(mapCell, Level, Element);

		if (mapCell.GetTopLevel() - Level >= -1)
		{
			Completed = true;
			UE_LOG(LogTemp, Log, TEXT("XLagMIPourGraundTask::Execute  Completed !!!!"));
		}
	}

	virtual bool IsSuccess() override { return Completed; }
	bool Completed = false;

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;
	float Level;
	TerrainElementEnum Element;
};
