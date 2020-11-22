#pragma once

#include "XLagTaskFactoryBase.h"
#include "XLagNPCTaskBase.h"
#include "XLagFmPloughTask.h"
#include "XLagFmSowTask.h"
#include "XLagFmGrowTask.h"
#include "XLagFmCropWaitTask.h"
#include "XLagFmCropTakeTask.h"
#include "XLagFmDischargeCropTask.h"
#include "XLagFmSearchCropStackTask.h"
#include "../../Common/ITerrainMapAccessor.h"
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
	std::shared_ptr<XLagNPCTaskBase> Cultivate(const int cropId)
	{
		auto crop = AXLagCropManager::GetCropsManager()->FindById(cropId);

		auto result = std::make_shared<XLagNPCTaskBase>();
		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(Sow(i, j, cropId));
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
				result->SubTasks.push_back(SearchCropStack(crop.ID));
				result->SubTasks.push_back(MoveToFind());
				result->SubTasks.push_back(Discharge());			
			}

		result->SubTasks.push_back(Repeat());

		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Plough(int x, int y)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmPloughTask(Place, x, y));
	}

	std::shared_ptr<XLagNPCTaskBase> Sow(int x, int y, const int cropId)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmSowTask(Place, x, y, cropId));
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

	std::shared_ptr<XLagNPCTaskBase> SearchCropStack(const int32 cropId)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagFmSearchCropStackTask(cropId));
	}

	std::shared_ptr<XLagNPCTaskBase> Discharge()
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagFmDischargeCropTask());
		return result;
	}
	

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};
