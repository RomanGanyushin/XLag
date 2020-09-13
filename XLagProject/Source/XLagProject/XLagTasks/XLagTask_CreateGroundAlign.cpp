#include "XLagTask_CreateGroundAlign.h"

UXLagTask_CreateGroundAlign::UXLagTask_CreateGroundAlign()
{
	ProfessionType = ProfessionTypeEnum::Builder;
	TaskTypeName = TEXT("GroundAlignTask");
	MaximalExecuterCount = 1;
	MinimalExecuterCount = 1;
	State = TaskStateEnum::Created;
}
