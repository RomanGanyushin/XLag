#pragma once

#include "XLagLooseStackBase.h"
#include "../XLagMinerals/Models/XLagMineralDesc.h"
#include "XLagMineralStack.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagMineralStack : public AXLagLooseStackBase
{
	GENERATED_BODY()

public:
	void Initialize(const FXLagMineralDesc& mineral, const int sizeX, const int sizeY);

	UPROPERTY(VisibleAnywhere, Category = "Mineral Stack Properties")
		FXLagMineralDesc ContentMineral;
};
