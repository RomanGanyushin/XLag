#pragma once

#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCFarmer.h"
#include "../../Common/ITerrainMapAccessor.h"

class XLagFmSowTask : public XLagNPCTaskBase
{
public:
	XLagFmSowTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y, const FXLagCropDescription crop)
		:Map(map), X(x), Y(y), Crop(crop)
	{
	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		if (Completed)
			return;

		auto farmer = dynamic_cast<AXLagNPCFarmer*>(npc);
		if (farmer == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagFmCropTask::Execute npc not Farmer"));
			return;
		}

		XLagDynamicTerrainMapItem& mapCell = Map->Point(X, Y);

		auto isFinished = farmer->Sow(mapCell, Crop, DeltaTime);
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
	FXLagCropDescription Crop;
};