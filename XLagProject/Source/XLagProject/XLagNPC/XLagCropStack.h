#pragma once
#include "XLagLooseStackBase.h"
#include "../XLagCrops/Models/XLagCropDescription.h"
#include "XLagCropStack.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagCropStack : public AXLagLooseStackBase
{
	GENERATED_BODY()

public:

	void Initialize(const FXLagCropDescription& crop, const int sizeX, const int sizeY);

	UPROPERTY(VisibleAnywhere, Category = "Crop Stack Properties")
		FXLagCropDescription ContentCrop;
};