#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "XLagWCCutTreeTask.h"
#include "XLagWCBroachTreeTask.h"
#include "XLagWCGetTreeTask.h"
#include "XLagWCPutTreeTask.h"

#include "../XLagNPC/XLagCuttableTreeBase.h"
#include "../XLagNPC/XLagTimberStack.h"

/*
 ������� ����� ��� ��������.
*/
class XLagWoodCutterTaskFactory
{
public:
	float CompliteDistanceToTree = 1.0f;
	float SpaceScale = 100.f;

public:
	// ������� ��������� ������.
	std::shared_ptr<XLagNPCTaskBase> BringTreeTaskCreate(AXLagCuttableTreeBase* tree, AXLagTimberStack *stack)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();
		result->SubTasks.push(MoveTo(tree->GetActorLocation()));
		result->SubTasks.push(CutTree(tree));
		result->SubTasks.push(BroachTree(tree));
		result->SubTasks.push(GetTree(tree));
		result->SubTasks.push(MoveTo(FVector(5000, 5000, 0)));
		result->SubTasks.push(PutTree(tree, stack));
		return result;
	}

	// �������� �� ��������� �������.
	std::shared_ptr<XLagNPCTaskBase> MoveTo(const FVector& location)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskMoveTo(location, CompliteDistanceToTree * SpaceScale));
		return result;
	}

	// ����� ������.
	std::shared_ptr<XLagNPCTaskBase> CutTree(AXLagCuttableTreeBase* tree)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCCutTreeTask(tree));
		return result;
	}

	// ��������� ������ �� ������.
	std::shared_ptr<XLagNPCTaskBase> BroachTree(AXLagCuttableTreeBase* tree)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCBroachTreeTask(tree));
		return result;
	}

	// ������ ������.
	std::shared_ptr<XLagNPCTaskBase> GetTree(AXLagCuttableTreeBase* tree)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCGetTreeTask(tree));
		return result;
	}

	// ������ � ������.
	std::shared_ptr<XLagNPCTaskBase> PutTree(AXLagCuttableTreeBase* tree, AXLagTimberStack* stack)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagWCPutTreeTask(tree, stack));
		return result;
	}
};