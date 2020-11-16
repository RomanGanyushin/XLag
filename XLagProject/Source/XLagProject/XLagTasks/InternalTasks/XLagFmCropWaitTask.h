#pragma once

#include "XLagNPCTaskBase.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../Common/CellOperationProcessing.h"
#include "../../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"
#include "../../XLagDynamicObject/ObjectModels/TerrainCropObject.h"

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
		XLagDynamicTerrainMapItemOperation operation(cell);

		if (!operation.HasObjectType(XLagDynamicObjectType::Crop))
		{
			Completed = true;
			return;
		}

		auto cropObject = operation.GetObjectByType(XLagDynamicObjectType::Crop);
		TerrainCropObject cropProperties(*cropObject);
		Completed = cropProperties.GetEvalution() == 100.0f;
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