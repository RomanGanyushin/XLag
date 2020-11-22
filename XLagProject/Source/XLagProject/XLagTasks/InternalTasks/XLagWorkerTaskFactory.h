#pragma once
#include "XLagNPCTaskBase.h"
#include "XLagTaskFactoryBase.h"
#include "XLagWrMineralWaitAndReserveTask.h"
#include "XLagWrTakeReservedMineralsTask.h"
#include "XLagWrTakeManualProductionTask.h"
#include "XLagWrPutProductionAtStackTask.h"
#include "XLagWrSearchProductStackTask.h"
#include "../../XLagProduction/XLagProductionSchemasManager.h"
#include "../../XLagProduction/Models/XLagProductionSchema.h"
#include "../../XLagMinerals/XLagMineralManager.h"
#include "../../Common/ITerrainMapAccessor.h"

class XLagWorkerTaskFactory : XLagTaskFactoryBase
{
public:
	XLagWorkerTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
		: Place(place)
	{
	}

	std::shared_ptr<XLagNPCTaskBase> Production(const int32 productId)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto center = Place->GetWorldPosition(Place->SizeX() / 2, Place->SizeY() / 2, GetPositionEnum::CenterHeghtPosition);
		result->SubTasks.push_back(MoveTo(center));

		TArray<int32> mineralComponentIds;
		TArray<int32> subProductComponentIds;

		auto mineralManager = AXLagMineralManager::GetMineralManager();
		auto productionManager = AXLagProductionSchemasManager::GetManagment();

		auto& productionSchema = productionManager->FindById(productId);

		for (auto & it : productionSchema.Recipe)
		{
			if (mineralManager->IsNameOfMineral(it.Name))
			{
				auto& mineral = mineralManager->FindByName(it.Name);
				mineralComponentIds.Add(mineral.ID);
			}
			else if (productionManager->IsNameOfProduct(it.Name))
			{
				auto& subProd = productionManager->FindByName(it.Name);
				subProductComponentIds.Add(subProd.ID);
			}
		}

		for (auto it : mineralComponentIds)
		{
			result->SubTasks.push_back(WaitAndReserveMineral(it, 10.0f));
			result->SubTasks.push_back(MoveToFind());
			result->SubTasks.push_back(TakeReservedMinerals(10.0f));
		}
		
		result->SubTasks.push_back(MoveTo(center));
		result->SubTasks.push_back(Production(productId, 10.0f));

		result->SubTasks.push_back(SearchProductStack(productId));
		result->SubTasks.push_back(MoveToFind());
		result->SubTasks.push_back(PutAtStack(productId));

		result->SubTasks.push_back(Repeat(/*where_if*/));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> WaitAndReserveMineral(const int32 mineralId, float quanity)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrMineralWaitAndReserveTask(mineralId, quanity));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> TakeReservedMinerals(float quanity)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrTakeReservedMineralsTask(quanity));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Production(const int productId, float quanity)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrTakeManualProductionTask(productId, quanity));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> PutAtStack(const int productId)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrPutProductionAtStackTask(productId));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> SearchProductStack(const int productId)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrSearchProductStackTask(productId));
		return result;
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};
