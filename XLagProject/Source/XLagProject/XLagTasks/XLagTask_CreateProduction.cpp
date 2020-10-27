#include "XLagTask_CreateProduction.h"

UXLagTask_CreateProduction::UXLagTask_CreateProduction()
{
	ProfessionType = ProfessionTypeEnum::Worker;
	TaskTypeName = TEXT("CreateProductionTask");
	MaximalExecuterCount = 1;
	MinimalExecuterCount = 1;
	State = TaskStateEnum::Created;
}
