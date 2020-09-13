#include "XLagTaskRegionBase.h"

void UXLagTaskRegionBase::SetRegion(std::shared_ptr<ITerrainMapAccessor> region)
{
	Region = region;
}