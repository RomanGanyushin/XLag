#pragma once

#include "XLagTaskFactoryBase.h"
#include "XLagNPCTaskBase.h"
#include "XLagWCCutTreeTask.h"
#include "XLagWCBroachTreeTask.h"
#include "XLagWCGetTreeTask.h"
#include "XLagWCPutTreeTask.h"

#include "../../XLagNPC/XLagCuttableTreeBase.h"
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

				if (!cellOperation.HasObjectType(XLagDynamicObjectType::Tree_))
					continue;

				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				result->SubTasks.push_back(MoveTo(pos));
				result->SubTasks.push_back(CutTree(cell));
				result->SubTasks.push_back(Delay(5));
				result->SubTasks.push_back(BroachTree(cell));
			}

		/*auto result = std::make_shared<XLagNPCTaskBase>();
		result->SubTasks.push_back(MoveTo(tree->GetActorLocation()));
		result->SubTasks.push_back(CutTree(tree));
		result->SubTasks.push_back(BroachTree(tree));
		result->SubTasks.push_back(GetTree(tree));
		result->SubTasks.push_back(MoveTo(FVector(5000, 5000, 0)));
		result->SubTasks.push_back(PutTree(tree, stack));*/
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
	std::shared_ptr<XLagNPCTaskBase> GetTree(AXLagCuttableTreeBase* tree)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCGetTreeTask(tree));
		return result;
	}

	// Положи в стопку.
	std::shared_ptr<XLagNPCTaskBase> PutTree(AXLagCuttableTreeBase* tree, AXLagTimberStack* stack)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCPutTreeTask(tree, stack));
		return result;
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};