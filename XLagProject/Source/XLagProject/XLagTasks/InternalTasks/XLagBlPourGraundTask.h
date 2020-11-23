#pragma once

#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCBuilderman.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"

class XLagBlPourGraundTask : public XLagNPCTaskBase
{
public:
	XLagBlPourGraundTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, float level, TerrainElementEnum element)
		:Map(map), X(x), Y(y), Level(level), Element(element)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto builder = dynamic_cast<AXLagNPCBuilderman*>(npc);
		if (builder == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagBlPourGraundTask::Execute npc not Builder"));
			return;
		}

		auto& mapCell = Map->Point(X, Y);
		Completed = builder->Pour(mapCell, Level, Element);
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
	bool Completed = false;

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;
	float Level;
	TerrainElementEnum Element;
};
