#pragma once

#include "XLagNPCTaskBase.h"
#include "../XLagNPC/XLagNPCBuilderman.h"
#include "../Common/ITerrainMapAccessor.h"

class XLagBlPourGraundTask : public XLagNPCTaskBase
{
public:
	XLagBlPourGraundTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, float level, TerrainElementEnum element)
		:Map(map), X(x), Y(y), Level(level), Element(element)
	{
#ifdef ENABLE_TASK_LOG
		UE_LOG(LogTemp, Log, TEXT("XLagBlPourGraundTask"));
#endif
	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		auto builder = dynamic_cast<AXLagNPCBuilderman*>(npc);
		if (builder == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagBlPourGraundTask::Execute npc not Builder"));
			return;
		}

		XLagDynamicTerrainMapItem& mapCell = Map->Point(X, Y);
		builder->Pour(mapCell, Level, Element);

		if (mapCell.GetTopLevel() - Level >= -1)
		{
			Completed = true;
			builder->Cancel();
			UE_LOG(LogTemp, Log, TEXT("XLagBlPourGraundTask::Execute  Completed !!!!"));
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
