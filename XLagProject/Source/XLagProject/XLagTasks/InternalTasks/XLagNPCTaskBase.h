#pragma once
#include <queue>
#include "memory"
#include "XLagNPCTaskContext.h"

class XLagNPCTaskBase
{
public:
	virtual ~XLagNPCTaskBase() = default;
public:
	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel = 0)
	{
		if (IsSuccess(context, subLevel))
			return;

		auto subTaskIndex = context->IndexForSubLevel(subLevel);
		SubTasks[subTaskIndex]->Execute(npc, context, DeltaTime, subLevel + 1);

		if (SubTasks[subTaskIndex]->IsSuccess(context, subLevel + 1))
		{
			context->IncrementForSubLevel(subLevel);
		}  
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel)
	{ 
		auto subTaskIndex = context->IndexForSubLevel(subLevel);
		return subTaskIndex >= SubTasks.size();
	}

	virtual bool IsFail() { return false; }

	virtual bool IsNpcRequire() { return true; }

	virtual bool IsAwait() { return false; }

public:
	std::vector<std::shared_ptr<XLagNPCTaskBase>> SubTasks;
};