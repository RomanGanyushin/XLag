#pragma once
#include "XLagNPCTaskBase.h"
#include "XLagTaskFactoryBase.h"
#include "XLagWrMineralWaitAndReserveTask.h"
#include "XLagWrTakeReservedMineralsTask.h"
#include "XLagWrTakeManualProductionTask.h"
#include "XLagWrPutProductionAtStackTask.h"
#include "../../XLagNPC/XLagProductStack.h"
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

	std::shared_ptr<XLagNPCTaskBase> Production(const FXLagProductionSchema* productionSchema, AXLagProductStack* stack)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto center = Place->GetWorldPosition(Place->SizeX() / 2, Place->SizeY() / 2, GetPositionEnum::CenterHeghtPosition);
		result->SubTasks.push_back(MoveTo(center));

		TArray<FString> mineralComponentNames;
		TArray<FString> subProductComponentNames;

		auto mineralManager = AXLagMineralManager::GetMineralManager();
		auto productionManager = AXLagProductionSchemasManager::GetManagment();

		for (auto & it : productionSchema->Recipe)
		{
			if (mineralManager->IsNameOfMineral(it.Name))
			{
				mineralComponentNames.Add(it.Name);
			}
			else if (productionManager->IsNameOfProduct(it.Name))
			{
				subProductComponentNames.Add(it.Name);
			}
		}

		for (auto it : mineralComponentNames)
		{
			result->SubTasks.push_back(WaitMineral(it, 10.0f));
			result->SubTasks.push_back(TakeReservedMinerals());
		}
		
		result->SubTasks.push_back(MoveTo(center));
		result->SubTasks.push_back(Production(productionSchema->Name, 10.0f));

		// Todo: переделать.
		auto stackPosition = stack->GetActorLocation();
		result->SubTasks.push_back(MoveTo(stackPosition));
		result->SubTasks.push_back(PutAtStack(productionSchema->Name, 10.0f, stack));

		result->SubTasks.push_back(Repeat(/*where_if*/));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> WaitMineral(FString mineralName, float quanity)
	{
		auto strMineralName = TCHAR_TO_UTF8(*mineralName);
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrMineralWaitAndReserveTask(strMineralName, quanity));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> TakeReservedMinerals()
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrTakeReservedMineralsTask(WorldCompliteDistance, MovingDeadline));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Production(FString productName, float quanity)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrTakeManualProductionTask(TCHAR_TO_UTF8(*productName), quanity));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> PutAtStack(FString productName, float quanity, AXLagProductStack* stack)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWrPutProductionAtStackTask(TCHAR_TO_UTF8(*productName), stack, quanity));
		return result;
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};
