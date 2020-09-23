#include  "XLagTask_ExtractMineralRegion.h"

UXLagTask_ExtractMineralRegion::UXLagTask_ExtractMineralRegion()
{
	ProfessionType = ProfessionTypeEnum::Miner;
	TaskTypeName = TEXT("ExtractMineralRegion");
	MaximalExecuterCount = 1;
	MinimalExecuterCount = 1;
	State = TaskStateEnum::Created;
}