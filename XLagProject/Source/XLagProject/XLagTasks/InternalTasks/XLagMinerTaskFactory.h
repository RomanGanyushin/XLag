#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "XLagMiSearchMineralTask.h"
#include "XLagMiExtractMineralTask.h"
#include "XLagMiDischargeMineralTask.h"
#include "../../XLagMinerals/Models/XLagMineralDesc.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagNPC/XLagMineralStack.h"

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

	// Поиск минерала.
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

	// Добыча минерала.
	std::shared_ptr<XLagNPCTaskBase> Extract(const FXLagMineralDesc mineral, AXLagMineralStack* stack)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto thisPoint = Place->Point(i, j);
				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);

				result->SubTasks.push(MoveTo(pos));
				result->SubTasks.push(Extract(i, j, mineral));
				result->SubTasks.push(MoveTo(stack->GetActorLocation()));
				result->SubTasks.push(Discharge(stack));
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