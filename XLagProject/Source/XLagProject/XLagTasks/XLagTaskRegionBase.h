#pragma once

#include "XLagTaskBase.h"
#include "XLagTaskRegionBase.generated.h"

UCLASS()
class UXLagTaskRegionBase : public UXLagTaskBase
{
	GENERATED_BODY()
public:
	virtual void SetRegion(std::shared_ptr<ITerrainMapAccessor> region);
private:
	std::shared_ptr<ITerrainMapAccessor> Region;
};