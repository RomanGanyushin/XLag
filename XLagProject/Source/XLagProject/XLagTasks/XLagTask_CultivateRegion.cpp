#include "XLagTask_CultivateRegion.h"

UXLagTask_CultivateRegion::UXLagTask_CultivateRegion()
{
	ProfessionType = ProfessionTypeEnum::Farmer;
	TaskTypeName = TEXT("CultivateRegionTask");
	MaximalExecuterCount = 1;
	MinimalExecuterCount = 1;
	State = TaskStateEnum::Created;
}