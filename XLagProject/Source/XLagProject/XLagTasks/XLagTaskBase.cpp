#include "XLagTaskBase.h"

bool UXLagTaskBase::CheckForNpcRequire()
{
	auto currentSubTask = GetCurrentSubTask();
	return currentSubTask->IsNpcRequire();
}

bool UXLagTaskBase::CheckForAwait()
{
	auto currentSubTask = GetCurrentSubTask();
	return currentSubTask->IsAwait();
}

bool UXLagTaskBase::CheckForRepeat()
{
	auto result = TaskContext.RequestForRepeat;
	TaskContext.RequestForRepeat = false;
	return result;
}

std::shared_ptr<XLagNPCTaskBase> UXLagTaskBase::GetCurrentSubTask()
{
	auto result = NpcTask;
	for (auto it  : TaskContext.GetExecutingVector())
	{
		result = result->SubTasks[it];
	}
	return result;
}