#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "XLagMiSearchMineralTask.h"
#include "../../XLagDynamicTerrain\Position/MinMaxLevelPlace.h"
#include "../../XLagMinerals/Models/XLagMineralDesc.h"
#include "../../Common/ITerrainMapAccessor.h"

/*
 Фабрика задач для шахтера.
*/
class XLagMinerTaskFactory
{
public:
	float CompliteDistanceToTree = 1.0f;
	float SpaceScale = 100.f;

public:
	XLagMinerTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
		: Place(place)
	{
	}

	// Выравнивнивание насыпанием.
	std::shared_ptr<XLagNPCTaskBase> Search(const FXLagMineralDesc mineral)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto thisPoint = Place->Point(i, j);
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);

				result->SubTasks.push(MoveTo(pos));
				result->SubTasks.push(Search(i, j, mineral));
			}

		return result;
	}

	// Двигайся до указанной локации.
	// Todo: вынести в базовый.
	std::shared_ptr<XLagNPCTaskBase> MoveTo(const FVector& location)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskMoveTo(location, CompliteDistanceToTree * SpaceScale, 10));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Search(int x, int y, const FXLagMineralDesc mineral)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagMiSearchMineralTask(Place, x, y, mineral));
		return result;
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};