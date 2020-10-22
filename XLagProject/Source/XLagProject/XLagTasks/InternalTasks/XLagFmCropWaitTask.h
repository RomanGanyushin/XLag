#pragma once

#include "XLagNPCTaskBase.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../Common/CellOperationProcessing.h"

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
		if (!cell.HasOnSurfaceResourceObjects(OnSurfaceResourceObjectsEnum::Crop))
		{
			isSuccess = true;
			return;
		}

		CellOperationProcessing operation(&cell, CellOperationEnum::Evolution);
		isSuccess = operation.IsComplete();
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return isSuccess;
	}

	bool IsNpcRequire() override { return false; }

	bool IsAwait() override { return true; }

private:
	bool isSuccess = false;
	std::shared_ptr<ITerrainMapAccessor> Map;
	int X;
	int Y;
};