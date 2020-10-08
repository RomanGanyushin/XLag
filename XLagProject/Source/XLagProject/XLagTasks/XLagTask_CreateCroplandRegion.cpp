#include "XLagTask_CreateCroplandRegion.h"

UXLagTask_CreateCroplandRegion::UXLagTask_CreateCroplandRegion()
{
	ProfessionType = ProfessionTypeEnum::Farmer;
	TaskTypeName = TEXT("CreateCroplandRegion");
	MaximalExecuterCount = 1;
	MinimalExecuterCount = 1;
	State = TaskStateEnum::Created;
}