#pragma once

#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCFarmer.h"
#include "../../Common/ITerrainMapAccessor.h"

class XLagFmPloughTask : public XLagNPCTaskBase
{
public:
	XLagFmPloughTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y)
		:Map(map), X(x), Y(y)
	{
#ifdef ENABLE_TASK_LOG
		UE_LOG(LogTemp, Log, TEXT("XLagFmCultivateTask"));
#endif
	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		auto farmer = dynamic_cast<AXLagNPCFarmer*>(npc);
		if (farmer == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagFmCultivateTask::Execute npc not Builder"));
			return;
		}

		XLagDynamicTerrainMapItem& mapCell = Map->Point(X, Y);
		
		auto isFinished = farmer->Plough(mapCell, DeltaTime);
		if (isFinished)
		{
			Completed = true;
		}
	}

	virtual bool IsSuccess() override { return Completed; }
	bool Completed = false;

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;	
};