#pragma once

#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCBuilderman.h"
#include "../../Common/ITerrainMapAccessor.h"

class XLagBlDigGraundTask : public XLagNPCTaskBase
{
public:
	XLagBlDigGraundTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, float level, bool keepTopLayer)
		:Map(map), X(x), Y(y), Level(level), KeepTopLayer(keepTopLayer)
	{
#ifdef ENABLE_TASK_LOG
		UE_LOG(LogTemp, Log, TEXT("XLagBlDigGraundTask"));
#endif
	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		auto builder = dynamic_cast<AXLagNPCBuilderman*>(npc);
		if (builder == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagBlDigGraundTask::Execute npc not Builder"));
			return;
		}

		XLagDynamicTerrainMapItem& mapCell = Map->Point(X, Y);
		builder->Dig(mapCell, Level, KeepTopLayer);

		if (mapCell.GetTopLevel() - Level <= 1)
		{
			Completed = true;
			builder->Cancel();
			UE_LOG(LogTemp, Log, TEXT("XLagBlDigGraundTask::Execute  Completed !!!!"));
		}
	}

	virtual bool IsSuccess() override { return Completed; }
	bool Completed = false;

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;
	float Level;
	bool KeepTopLayer;
};
