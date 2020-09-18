#include "XLagTask_SearchMineralRegion.h"

UXLagTask_SearchMineralRegion::UXLagTask_SearchMineralRegion()
{
	ProfessionType = ProfessionTypeEnum::Miner;
	TaskTypeName = TEXT("SearchMineralTask");
	MaximalExecuterCount = 1;
	MinimalExecuterCount = 1;
	State = TaskStateEnum::Created;
}