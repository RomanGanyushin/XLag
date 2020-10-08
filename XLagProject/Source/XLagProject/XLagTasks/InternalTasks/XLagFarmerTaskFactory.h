#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "XLagFmCultivateTask.h"

#include "../../Common/ITerrainMapAccessor.h"

/*
 Фабрика задач для строителя.
*/
class XLagFarmerTaskFactory
{
public:
	float CompliteDistanceToTree = 1.0f;
	float SpaceScale = 100.f;

public:
	XLagFarmerTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
		: Place(place)
	{
	}

	// Обработка.
	std::shared_ptr<XLagNPCTaskBase> Cultivate()
	{
		auto result = std::make_shared<XLagNPCTaskBase>();
			for (int i = 0; i < Place->SizeX(); i++)
				for (int j = 0; j < Place->SizeY(); j++)
				{				
					auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
					result->SubTasks.push(MoveTo(pos));
					result->SubTasks.push(Cultivate(i, j));
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

	std::shared_ptr<XLagNPCTaskBase> Cultivate(int x, int y)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmCultivateTask(Place, x, y));
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};
