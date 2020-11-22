#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagTaskFactoryBase.h"
#include "XLagMiSearchMineralTask.h"
#include "XLagMiExtractMineralTask.h"
#include "XLagMiDischargeMineralTask.h"
#include "XLagMiSearchMineralStackTask.h"
#include "../../XLagMinerals/Models/XLagMineralDesc.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagNPC/XLagMineralStack.h"
#include "../../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"

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
	std::shared_ptr<XLagNPCTaskBase> Search(const int32 mineralId)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto thisPoint = Place->Point(i, j);
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				

				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(Search(i, j, mineralId));				
			}

		return result;
	}

	// Добыча минерала.
	std::shared_ptr<XLagNPCTaskBase> Extract(const int32 mineralId)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto thisPoint = Place->Point(i, j);
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);

				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(Extract(i, j, mineralId));
				result->SubTasks.push_back(SearchMineralStack(mineralId));
				result->SubTasks.push_back(MoveToFind());
				result->SubTasks.push_back(Discharge());
			}

		auto place = Place.get();
		auto where_if = [mineralId, place]()
		{
			for (int i = 0; i < place->SizeX(); i++)
				for (int j = 0; j < place->SizeY(); j++)
				{
					if (XLagDynamicTerrainMapItemOperation(place->Point(i,j)).CheckForMineral(mineralId))
						return true;
				}
				
			return false;
		};

		result->SubTasks.push_back(Repeat(where_if));

		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Search(int x, int y, const int32 mineralId)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagMiSearchMineralTask(Place, x, y, mineralId));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Extract(int x, int y, const int32 mineralId)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagMiExtractMineralTask(Place, x, y, mineralId));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Discharge()
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagMiDischargeMineralTask());
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> SearchMineralStack(const int32 mineralId)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagMiSearchMineralStackTask(mineralId));
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};