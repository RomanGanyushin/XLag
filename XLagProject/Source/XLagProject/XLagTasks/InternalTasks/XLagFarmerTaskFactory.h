#pragma once

#include "XLagTaskFactoryBase.h"
#include "XLagNPCTaskBase.h"
#include "XLagFmPloughTask.h"
#include "XLagFmSowTask.h"
#include "XLagFmGrowTask.h"
#include "XLagFmCropWaitTask.h"
#include "XLagFmCropTakeTask.h"
#include "XLagFmDischargeCropTask.h"

#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagNPC/XLagCropStack.h"
/*
 Фабрика задач для строителя.
*/
class XLagFarmerTaskFactory : protected XLagTaskFactoryBase
{
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
				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(Plough(i, j));
			}

		return result;
	}

	// Сеяние.
	std::shared_ptr<XLagNPCTaskBase> Cultivate(const FXLagCropDescription crop, AXLagCropStack* stack)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();
		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(Sow(i, j, crop));
			}

		result->SubTasks.push_back(Delay(crop.TimeLife / 2));

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				result->SubTasks.push_back(MoveTo(pos));		
				result->SubTasks.push_back(Grow(i,j));
			}

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				result->SubTasks.push_back(CropWait(i, j));
			}

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(CropTake(i, j));
				result->SubTasks.push_back(MoveTo(stack->GetActorLocation()));
				result->SubTasks.push_back(Discharge(stack));			
			}

		result->SubTasks.push_back(Repeat());

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

	std::shared_ptr<XLagNPCTaskBase> Grow(int x, int y)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmGrowTask(Place, x, y));
	}

	std::shared_ptr<XLagNPCTaskBase> CropWait(int x, int y)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmCropWaitTask(Place, x, y));
	}

	std::shared_ptr<XLagNPCTaskBase> CropTake(int x, int y)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmCropTakeTask(Place, x, y));
	}

	std::shared_ptr<XLagNPCTaskBase> Discharge(AXLagCropStack* stack)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagFmDischargeCropTask(stack));
		return result;
	}
	

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};
