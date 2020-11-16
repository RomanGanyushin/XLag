#pragma once

#include "XLagTaskFactoryBase.h"
#include "XLagNPCTaskBase.h"
#include "XLagWCCutTreeTask.h"
#include "XLagWCBroachTreeTask.h"
#include "XLagWCGetTreeTask.h"
#include "XLagWCPutTreeTask.h"
#include "../../XLagNPC/XLagTimberStack.h"

/*
 Фабрика задач для лесоруба.
*/
class XLagWoodCutterTaskFactory : XLagTaskFactoryBase
{
public:
	XLagWoodCutterTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
		: Place(place)
	{
	}

	// Принеси указанное дерево.
	std::shared_ptr<XLagNPCTaskBase> BringTreeTaskCreate(AXLagTimberStack *stack)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				auto& cell = Place->Point(i, j);
				XLagDynamicTerrainMapItemOperation cellOperation(cell);

				if (!cellOperation.HasObjectType(XLagDynamicObjectType::Tree))
					continue;

				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(CutTree(cell));
				result->SubTasks.push_back(Delay(5));
				result->SubTasks.push_back(BroachTree(cell));
				result->SubTasks.push_back(Delay(5));
				result->SubTasks.push_back(GetTree(cell));
				result->SubTasks.push_back(MoveTo(stack->GetActorLocation())); // Переделать.
				result->SubTasks.push_back(PutTree(stack)); // Переделать.
				result->SubTasks.push_back(Delay(5));
			}

		return result;
	}

	// Сруби дерево.
	std::shared_ptr<XLagNPCTaskBase> CutTree(FXLagDynamicTerrainMapItem& cell)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCCutTreeTask(cell));
		return result;
	}

	// Обработай дерево до бревна.
	std::shared_ptr<XLagNPCTaskBase> BroachTree(FXLagDynamicTerrainMapItem& cell)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCBroachTreeTask(cell));
		return result;
	}

	// Возьми бревно.
	std::shared_ptr<XLagNPCTaskBase> GetTree(FXLagDynamicTerrainMapItem& cell)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCGetTreeTask(cell));
		return result;
	}

	// Положи в стопку.
	std::shared_ptr<XLagNPCTaskBase> PutTree(AXLagTimberStack* stack)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCPutTreeTask(stack));
		return result;
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};