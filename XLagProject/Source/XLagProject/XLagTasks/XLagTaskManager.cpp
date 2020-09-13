#include "XLagTaskManager.h"
#include "InternalTasks/XLagBuilderTaskFactory.h"
#include "XLagTask_CreateGroundAlign.h"

AXLagTaskManager::AXLagTaskManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AXLagTaskManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto IsSomeNpcReleased = false;

	for (auto& it : Tasks)
	{
		if (it->State != TaskStateEnum::InProgess)
			continue;

		for (auto &e : it->Executers)
		{
			it->NpcTask->Execute(e, DeltaTime);
		}

		if (it->NpcTask->IsSuccess())
		{
			for (auto &e : it->Executers)
			{
				e->FreeOf(it);
				it->State = TaskStateEnum::Done;
				IsSomeNpcReleased = true;
			}
		}
	}

	if (IsSomeNpcReleased)
	{
		SearchAndChooseExecuters();
	}
}

void AXLagTaskManager::CreateGroundAlignTask(AXLagSelectComponent *select, GroundAlignTypeEnum type, TerrainElementEnum pourElement, float zParameter, int RequiredWorkerNumber)
{
	// Создает задачу.
	auto newTask = NewObject<UXLagTask_CreateGroundAlign>();
	newTask->SetAlignRegion(select->Select);
	newTask->State = TaskStateEnum::Recruitment;
	
	// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;
	
	switch (type)
	{
		case Diging:
		{
			task->SubTasks.push(XLagBuilderTaskFactory(place).AlignDigPlace());

			if (zParameter != 0.0f)
			{
				task->SubTasks.push(XLagBuilderTaskFactory(place).DigPlace(zParameter));
			}			
		}
		break;

		case Pouring:
		{
			task->SubTasks.push(XLagBuilderTaskFactory(place).AlignPourPlace(pourElement));

			if (zParameter != 0.0f)
			{
				task->SubTasks.push(XLagBuilderTaskFactory(place).PourPlace(zParameter, pourElement));
			}
		}
		break;
	}
	
	newTask->NpcTask = task;

	// Добавляем в стек.
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

void AXLagTaskManager::SearchAndChooseExecuters()
{
	for (auto& it : Tasks)
	{
		if (it->State != TaskStateEnum::Recruitment)
			continue;

		SearchAndChooseExecuters(it);
	}
}

void AXLagTaskManager::SearchAndChooseExecuters(UXLagTaskBase* task)
{
	_requestForExecution.Reset();
	PerformersSearchEvent.Broadcast(this, task);

	if (!_requestForExecution.Contains(task))
		return;

	auto& executers = _requestForExecution[task];
	
	auto takeExecutorCount = std::min(task->MaximalExecuterCount, executers.Num());
	for (int execIndex = 0; execIndex < takeExecutorCount; execIndex++)
	{
		// Добавляем ссылку на исполнителя к задаче.
		task->Executers.Add(executers[execIndex]);

		// Принимаем предложение на работу.
		executers[execIndex]->OfferAccept(task);
	}

	if (task->Executers.Num() >= task->MinimalExecuterCount)
	{
		task->State = TaskStateEnum::InProgess;
	}

	_requestForExecution.Reset();
}