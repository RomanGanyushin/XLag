#include "XLagTask_CreateBuilding.h"

UXLagTask_CreateBuilding::UXLagTask_CreateBuilding()
{
	ProfessionType = ProfessionTypeEnum::Builder;
	TaskTypeName = TEXT("CreateBuildingTask");
	MaximalExecuterCount = 1;
	MinimalExecuterCount = 1;
	State = TaskStateEnum::Created;
}