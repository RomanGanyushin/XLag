#pragma once
#include "XLagTaskBase.h"
#include "XLagTask_CreateGroundAlign.generated.h"

UCLASS()
class UXLagTask_CreateGroundAlign : public UXLagTaskBase
{
	GENERATED_BODY()
		UXLagTask_CreateGroundAlign()
	{
		ProfessionType = ProfessionTypeEnum::Builder;
		TaskTypeName = TEXT("GroundAlignTask");
		MaximalExecuterCount = 1;
		MinimalExecuterCount = 1;
		State = TaskStateEnum::Created;
	}

public:
	void SetAlignRegion(std::shared_ptr<ITerrainMapAccessor> region)
	{
		Region = region;
	}
private:
	std::shared_ptr<ITerrainMapAccessor> Region;
};