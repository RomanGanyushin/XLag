#pragma once
#include <queue>
#include "memory"

//#define ENABLE_TASK_LOG

class XLagNPCTaskBase
{
public:
	virtual ~XLagNPCTaskBase() = default;
public:
	virtual void Execute(ACharacter *npc, float DeltaTime)
	{
		if (SubTasks.empty())
			return;

		SubTasks.front()->Execute(npc, DeltaTime);

		if (SubTasks.front()->IsSuccess())
		{
			SubTasks.pop();

#ifdef ENABLE_TASK_LOG
			UE_LOG(LogTemp, Log, TEXT("XLagNPCTaskBase: SubTasks Complite"));
#endif
		}
	}
	virtual bool IsSuccess() { return SubTasks.empty(); }
	virtual bool IsFail() { return false; }

public:
	std::queue<std::shared_ptr<XLagNPCTaskBase>> SubTasks;
};