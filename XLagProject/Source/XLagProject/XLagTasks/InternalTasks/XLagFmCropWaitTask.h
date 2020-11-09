#pragma once

#include "XLagNPCTaskBase.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../Common/CellOperationProcessing.h"
#include "../../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"

class XLagFmCropWaitTask : public XLagNPCTaskBase
{
public:
	XLagFmCropWaitTask(std::shared_ptr<ITerrainMapAccessor> map, int x, int y)
		:Map(map), X(x), Y(y)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		auto& cell = Map->Point(X, Y);
		if (!XLagDynamicTerrainMapItemOperation(cell).HasOnSurfaceResourceObjects(OnSurfaceResourceObjectsEnum::Crop))
		{
			Completed = true;
			return;
		}

		CellOperationProcessing operation(&cell, CellOperationEnum::Evolution);
		Completed = operation.IsComplete();
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return Completed;
	}

	bool IsNpcRequire() override { return false; }

	bool IsAwait() override { return true; }

private:
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;
};