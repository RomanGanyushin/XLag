#include "XLagTaskManager.h"

AXLagTaskManager::AXLagTaskManager()
{
	
}

void AXLagTaskManager::CreateGroundAlignTask(AXLagSelectComponent *select, GroundAlignType type, float zParameter)
{
	auto newTask = NewObject<UXLagTask_CreateGroundAlign>();
	newTask->SetAlignRegion(select->Select);
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);
}

void AXLagTaskManager::ApplyForTask(AXLagNPCBase *npc, UXLagTaskBase* task)
{
	if (!_requestForExecution.Contains(task))
	{
		_requestForExecution.Add(task);
	}
	_requestForExecution[task].Add(npc);
}


void AXLagTaskManager::SearchAndChooseExecuters(UXLagTaskBase* task)
{
	_requestForExecution.Reset();
	PerformersSearchEvent.Broadcast(this, task);

	if (!_requestForExecution.Contains(task))
		return;

	auto& executers = _requestForExecution[task];
	if (executers.Num() < task->MaximalExecuterCount)
	{
		//CancelationTask(task);
	}

	auto takeExecutorCount = std::min(task->MaximalExecuterCount, executers.Num());
	for (int execIndex = 0; execIndex < takeExecutorCount; execIndex++)
	{
		// ƒобавл€ем ссылку на исполнител€ к задаче.
		task->Executers.Add(executers[execIndex]);

		// ѕринимаем предложение на работу.
		executers[execIndex]->OfferAccept(task);
	}

	task->State = TaskStateEnum::WaitForBegin;
	_requestForExecution.Reset();
}