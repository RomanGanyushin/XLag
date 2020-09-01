#include "XLagTaskManager.h"

AXLagTaskManager::AXLagTaskManager()
{

}

void AXLagTaskManager::CreateGroundAlignTask(AXLagSelectComponent *select, GroundAlignType type, float zParameter)
{
	auto newTask = NewObject<UXLagTask_CreateGroundAlign>();
	newTask->ProfessionType = Builder;
	newTask->TaskTypeName = "GroundAlignTask";
	newTask->Select = select;
	Tasks.Add(newTask);
}

void AXLagTaskManager::TakeTask(UXLagTaskBase* task, AXLagNPCBase *npc)
{

}