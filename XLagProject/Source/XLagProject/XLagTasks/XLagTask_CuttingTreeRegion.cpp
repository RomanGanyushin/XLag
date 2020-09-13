#include "XLagTask_CuttingTreeRegion.h"

UXLagTask_CuttingTreeRegion::UXLagTask_CuttingTreeRegion()
{
	ProfessionType = ProfessionTypeEnum::Treecutter;
	TaskTypeName = TEXT("CuttingTreeRegion");
	MaximalExecuterCount = 1;
	MinimalExecuterCount = 1;
	State = TaskStateEnum::Created;
}