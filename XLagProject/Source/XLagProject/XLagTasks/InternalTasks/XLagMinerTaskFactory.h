#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagTaskFactoryBase.h"
#include "XLagMiSearchMineralTask.h"
#include "XLagMiExtractMineralTask.h"
#include "XLagMiDischargeMineralTask.h"
#include "../../XLagMinerals/Models/XLagMineralDesc.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagNPC/XLagMineralStack.h"

/*
 Фабрика задач для шахтера.
*/
class XLagMinerTaskFactory : XLagTaskFactoryBase
{
public:
	float CompliteDistanceToTree = 1.0f;
	float SpaceScale = 100.f;

public:
	XLagMinerTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
		: Place(place)
	{
	}

	// Поиск минерала.
	std::shared_ptr<XLagNPCTaskBase> Search(const FXLagMineralDesc mineral)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto thisPoint = Place->Point(i, j);
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				

				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(Search(i, j, mineral));				
			}

		return result;
	}

	// Добыча минерала.
	std::shared_ptr<XLagNPCTaskBase> Extract(const FXLagMineralDesc mineral, AXLagMineralStack* stack)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto thisPoint = Place->Point(i, j);
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);

				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(Extract(i, j, mineral));
				result->SubTasks.push_back(MoveTo(stack->GetActorLocation()));
				result->SubTasks.push_back(Discharge(stack));
			}

		auto mineralId = mineral.ID;
		auto place = Place.get();
		auto where_if = [mineralId, place]()
		{
			for (int i = 0; i < place->SizeX(); i++)
				for (int j = 0; j < place->SizeY(); j++)
				{
					if (place->Point(i,j).CheckForMineral(mineralId))
						return true;
				}
				
			return false;
		};

		result->SubTasks.push_back(Repeat(where_if));

		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Search(int x, int y, const FXLagMineralDesc mineral)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagMiSearchMineralTask(Place, x, y, mineral));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Extract(int x, int y, const FXLagMineralDesc mineral)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagMiExtractMineralTask(Place, x, y, mineral));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Discharge(AXLagMineralStack* stack)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagMiDischargeMineralTask(stack));
		return result;
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};