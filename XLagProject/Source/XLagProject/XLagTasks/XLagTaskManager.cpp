#include "XLagTaskManager.h"
#include "XLagBuilderTaskFactory.h"

AXLagTaskManager::AXLagTaskManager()
{
	
}

void AXLagTaskManager::Tick(float DeltaTime)
{
	for (auto& it : Tasks)
	{
		for (auto &e : it->Executers)
		{
			it->NpcTask->Execute(e, DeltaTime);
		}
	}
}

void AXLagTaskManager::CreateGroundAlignTask(AXLagSelectComponent *select, GroundAlignType type, float zParameter)
{
	// ������� ������.
	auto newTask = NewObject<UXLagTask_CreateGroundAlign>();
	newTask->SetAlignRegion(select->Select);
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);

	// ��������� ����������.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = newTask->Select->Select;
	task->SubTasks.push(XLagBuilderTaskFactory(place).AlignDigPlace());
	newTask->NpcTask = task;
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
		// ��������� ������ �� ����������� � ������.
		task->Executers.Add(executers[execIndex]);

		// ��������� ����������� �� ������.
		executers[execIndex]->OfferAccept(task);
	}

	task->State = TaskStateEnum::WaitForBegin;
	_requestForExecution.Reset();
}