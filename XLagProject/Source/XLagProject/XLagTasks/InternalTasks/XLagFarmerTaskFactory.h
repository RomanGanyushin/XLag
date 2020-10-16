#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "XLagFmPloughTask.h"
#include "XLagFmSowTask.h"

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
	std::shared_ptr<XLagNPCTaskBase> Plough()
	{
		auto result = std::make_shared<XLagNPCTaskBase>();
		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				result->SubTasks.push(MoveTo(pos));
				result->SubTasks.push(Plough(i, j));
			}

		return result;
	}

	// Сеяние.
	std::shared_ptr<XLagNPCTaskBase> Sow(const FXLagCropDescription crop)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();
		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				result->SubTasks.push(MoveTo(pos));
				result->SubTasks.push(Sow(i, j, crop));
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

	std::shared_ptr<XLagNPCTaskBase> Plough(int x, int y)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmPloughTask(Place, x, y));
	}

	std::shared_ptr<XLagNPCTaskBase> Sow(int x, int y, const FXLagCropDescription crop)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmSowTask(Place, x, y, crop));
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};
