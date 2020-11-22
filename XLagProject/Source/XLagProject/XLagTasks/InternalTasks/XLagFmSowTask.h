#pragma once

#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCFarmer.h"
#include "../../Common/ITerrainMapAccessor.h"

class XLagFmSowTask : public XLagNPCTaskBase
{
public:
	XLagFmSowTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, const int32 cropId)
		:Map(map), X(x), Y(y), CropId(cropId)
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

		auto isFinished = farmer->Sow(mapCell, CropId, DeltaTime);
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
	const int32 CropId;
};