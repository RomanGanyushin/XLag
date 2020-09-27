#include "XLagTaskManager.h"
#include "InternalTasks/XLagBuilderTaskFactory.h"
#include "InternalTasks/XLagWoodCutterTaskFactory.h"
#include "InternalTasks/XLagMinerTaskFactory.h"
#include "../XLagDynamicTerrain/Filters/SurfaceResourceMapItemFilter.h"
#include "../XLagNpc/XLagNPCSwapManagement.h"
#include "XLagTask_CreateGroundAlign.h"
#include "XLagTask_CuttingTreeRegion.h"
#include "XLagTask_SearchMineralRegion.h"
#include "XLagTask_ExtractMineralRegion.h"

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
	newTask->SetRegion(select->Select);
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

void AXLagTaskManager::CreateCuttingTreeTask(AXLagSelectComponent *select, AXLagTimberStack *timberStack, int RequiredWorkerNumber)
{
	// Создает задачу.
	auto newTask = NewObject<UXLagTask_CuttingTreeRegion>();
	newTask->SetRegion(select->Select);
	newTask->State = TaskStateEnum::Recruitment;

	// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;

	// Получаем клетки из региона где есть деревья.
	auto mapRequireTrees = place->GetFilteredItems(SurfaceResourceMapItemFilter(OnSurfaceResourceObjectsEnum::Tree));
	if (mapRequireTrees.empty())
		return;

	auto swapper = AXLagNPCSwapManagement::GetManagment();

	for (auto mapItemPtr : mapRequireTrees)
	{
		long placeId = mapItemPtr->GetId();
		auto ppTree = swapper->SwapedTrees.FindByPredicate([placeId](auto& pt) {return pt->PlaceId == placeId; });
		if (ppTree == nullptr)
			continue;

		task->SubTasks.push(XLagWoodCutterTaskFactory().BringTreeTaskCreate(*ppTree, timberStack));
	}


	newTask->NpcTask = task;

	// Добавляем в стек.
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);
}

void AXLagTaskManager::CreateSearchMineralTask(AXLagSelectComponent *select, const FXLagMineralDesc mineral, int RequiredWorkerNumber)
{
	// Создает задачу.
	auto newTask = NewObject<UXLagTask_SearchMineralRegion>();
	newTask->SetRegion(select->Select);
	newTask->State = TaskStateEnum::Recruitment;

	// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;
	task->SubTasks.push(XLagMinerTaskFactory(place).Search(mineral));
	newTask->NpcTask = task;

	// Добавляем в стек.
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);
}

void AXLagTaskManager::CreateExtractMineralTask(AXLagSelectComponent *select, const FXLagMineralDesc mineral, AXLagMineralStack* stack, int RequiredWorkerNumber)
{
	if (stack == nullptr) // Если не указано куда нести, то первый.
	{
		auto swapManagment = AXLagNPCSwapManagement::GetManagment();
		auto pstack = swapManagment->SwapedMineralStacks
			.FindByPredicate([mineral](auto it) { return it->ContentMineral.ID == mineral.ID; });

		if(pstack != nullptr)
		{
			stack = *pstack;
		}
		else // Не найдено место для склада, то создаем.
		{
			auto manager = AXLagNPCSwapManagement::GetManagment();
			stack = manager->DoSwapMineralStack(mineral);
		}
	}
	
	// Создает задачу.
	auto newTask = NewObject<UXLagTask_ExtractMineralRegion>();
	newTask->SetRegion(select->Select);
	newTask->State = TaskStateEnum::Recruitment;

	// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;
	task->SubTasks.push(XLagMinerTaskFactory(place).Extract(mineral, stack));
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