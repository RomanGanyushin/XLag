#include "XLagTaskManager.h"
#include "InternalTasks/XLagBuilderTaskFactory.h"
#include "InternalTasks/XLagWoodCutterTaskFactory.h"
#include "InternalTasks/XLagMinerTaskFactory.h"
#include "InternalTasks/XLagFarmerTaskFactory.h"
#include "InternalTasks/XLagWorkerTaskFactory.h"
#include "../XLagDynamicTerrain/Filters/SurfaceResourceMapItemFilter.h"
#include "../XLagNpc/XLagNPCSwapManagement.h"
#include "../XLagBuildings/XLagBuildingManager.h"
#include "XLagTask_CreateGroundAlign.h"
#include "XLagTask_CuttingTreeRegion.h"
#include "XLagTask_SearchMineralRegion.h"
#include "XLagTask_ExtractMineralRegion.h"
#include "XLagTask_CreateBuilding.h"
#include "XLagTask_CreateCroplandRegion.h"
#include "XLagTask_CultivateRegion.h"
#include "XLagTask_CreateProduction.h"

AXLagTaskManager::AXLagTaskManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AXLagTaskManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	for (auto& it : Tasks)
	{
		if (it->State != TaskStateEnum::InProgess && it->State != TaskStateEnum::Waiting)
			continue;

		auto isTaskAwait = it->CheckForAwait();
		auto isNpcRequireTask = it->CheckForNpcRequire();
		

		if (isTaskAwait && it->State != TaskStateEnum::Waiting)
		{
			FreeTask(it);
			it->State = TaskStateEnum::Waiting;
		}
		else if(isNpcRequireTask && it->State == TaskStateEnum::Waiting)
		{
			it->State = TaskStateEnum::Recruitment;
		}

		if (isNpcRequireTask)
		{
			for (auto &e : it->Executers) // TODO: Тут может быть нулевой перс. Надо проверить и удалить из исполнителей.
			{
				it->NpcTask->Execute(e, &it->TaskContext, DeltaTime);
			}
		}
		else
		{
			it->NpcTask->Execute(nullptr, &it->TaskContext, DeltaTime);
		}

		if (it->NpcTask->IsSuccess(&it->TaskContext, 0))
		{
			FreeTask(it);
			it->State = TaskStateEnum::Done;			
		}

		auto isRepeat = it->CheckForRepeat();
		if (isRepeat)
		{
			it->State = TaskStateEnum::Waiting;
			it->NpcTask->Reset();
			it->TaskContext.Reset();
		}
	}
	
	SearchAndChooseExecuters();	
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
			task->SubTasks.push_back(XLagBuilderTaskFactory(place).AlignDigPlace());

			if (zParameter != 0.0f)
			{
				task->SubTasks.push_back(XLagBuilderTaskFactory(place).DigPlace(zParameter));
			}			
		}
		break;

		case Pouring:
		{
			task->SubTasks.push_back(XLagBuilderTaskFactory(place).AlignPourPlace(pourElement));

			if (zParameter != 0.0f)
			{
				task->SubTasks.push_back(XLagBuilderTaskFactory(place).PourPlace(zParameter, pourElement));
			}
		}
		break;
	}
	
	newTask->NpcTask = task;

	// Добавляем в стек.
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);	
}

void AXLagTaskManager::CreateCuttingTreeTask(AXLagSelectComponent *select, int RequiredWorkerNumber)
{
	// Создает задачу.
	auto newTask = NewObject<UXLagTask_CuttingTreeRegion>();
	newTask->SetRegion(select->Select);
	newTask->State = TaskStateEnum::Recruitment;

	// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;

	task->SubTasks.push_back(XLagWoodCutterTaskFactory(place).BringTreeTaskCreate());
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
	task->SubTasks.push_back(XLagMinerTaskFactory(place).Search(mineral));
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
	task->SubTasks.push_back(XLagMinerTaskFactory(place).Extract(mineral, stack));
	newTask->NpcTask = task;

	// Добавляем в стек.
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);	
}

void AXLagTaskManager::CreateCroplandTask(AXLagSelectComponent *select, int RequiredWorkerNumber)
{
	// Создает задачу.
	auto newTask = NewObject<UXLagTask_CreateCroplandRegion>();
	newTask->SetRegion(select->Select);
	newTask->State = TaskStateEnum::Recruitment;

	//// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;
	task->SubTasks.push_back(XLagFarmerTaskFactory(place).Plough());
	newTask->NpcTask = task;

	// Добавляем в стек.
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);
}

void AXLagTaskManager::CreateCultivationTask(AXLagSelectComponent *select, const FXLagCropDescription crop, int RequiredWorkerNumber)
{
	// Создает задачу.
	auto newTask = NewObject<UXLagTask_CultivateRegion>();
	newTask->SetRegion(select->Select);
	newTask->State = TaskStateEnum::Recruitment;

	//// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;
	task->SubTasks.push_back(XLagFarmerTaskFactory(place).Cultivate(crop));
	newTask->NpcTask = task;

	// Добавляем в стек.
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);
}

void AXLagTaskManager::CreateBuildingTask(const FXLagBuildingDescription& buildingDescription, int RequiredWorkerNumber)
{
	auto managment = AXLagBuildingManager::GetManagment();
	auto building = managment->BuildingSiteFound(buildingDescription);

	// Создает задачу.
	auto newTask = NewObject<UXLagTask_CreateBuilding>();

	// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	task->SubTasks.push_back(XLagBuilderTaskFactory(std::shared_ptr<ITerrainMapAccessor>()).Build(building));
	newTask->NpcTask = task;

	// Добавляем в стек.
	Tasks.Add(newTask);

	SearchAndChooseExecuters(newTask);
}

void AXLagTaskManager::CreateProductionTask(const FXLagProductionSchema& productionSchema, AXLagSelectComponent *select, float Quanity, int RequiredWorkerNumber)
{
	AXLagProductStack* stack = nullptr;
	if (stack == nullptr) // Если не указано куда нести, то первый.
	{
		auto swapManagment = AXLagNPCSwapManagement::GetManagment();
		auto pstack = swapManagment->SwapedProductStacks
			.FindByPredicate([](auto it) { return true; });

		if (pstack != nullptr)
		{
			stack = *pstack;
		}
		else // Не найдено место для склада, то создаем.
		{
			auto manager = AXLagNPCSwapManagement::GetManagment();
			stack = manager->DoSwapProductStack(productionSchema);
		}
	}

	// Создает задачу.
	auto newTask = NewObject<UXLagTask_CreateProduction>();
	newTask->SetRegion(select->Select);
	newTask->State = TaskStateEnum::Recruitment;

	//// Планируем выполнение.
	auto task = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskBase);
	auto place = select->Select;
	task->SubTasks.push_back(XLagWorkerTaskFactory(place).Production(&productionSchema, stack));
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

void AXLagTaskManager::FreeTask(UXLagTaskBase* task)
{
	for (auto &e : task->Executers)
	{
		e->FreeOf(task);
	}	

	task->Executers.Reset();
}