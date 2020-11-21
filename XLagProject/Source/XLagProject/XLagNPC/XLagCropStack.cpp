#include "XLagCropStack.h"

void AXLagCropStack::Initialize(const FXLagCropDescription& crop, const int sizeX, const int sizeY)
{
	ContentCrop = crop;
	SizeX = sizeX;
	SizeY = sizeY;

	if (crop.CropPresentMaterial != nullptr)
	{
		ThisStack->SetMaterial(0, crop.CropPresentMaterial);
	}

	CreateView();
}