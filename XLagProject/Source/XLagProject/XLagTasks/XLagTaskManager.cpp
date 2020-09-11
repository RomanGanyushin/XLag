#include "XLagTaskManager.h"
#include "XLagBuilderTaskFactory.h"

AXLagTaskManager::AXLagTaskManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AXLagTaskManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	// Создает задачу.
	auto newTask = NewObject<UXLagTask_CreateGroundAlign>();
	newTask->SetAlignRegion(select->Select);
	
	SearchAndChooseExecuters(newTask);

	// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;
	task->SubTasks.push(XLagBuilderTaskFactory(place).AlignDigPlace());
	newTask->NpcTask = task;

	Tasks.Add(newTask);
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
		// Добавляем ссылку на исполнителя к задаче.
		task->Executers.Add(executers[execIndex]);

		// Принимаем предложение на работу.
		executers[execIndex]->OfferAccept(task);
	}

	task->State = TaskStateEnum::WaitForBegin;
	_requestForExecution.Reset();
}