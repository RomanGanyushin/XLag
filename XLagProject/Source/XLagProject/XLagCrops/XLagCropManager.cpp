#include "XLagCropManager.h"

AXLagCropManager::AXLagCropManager()
{
}

void AXLagCropManager::CompliteCreate()
{
	auto element_id = 1;
	for (auto& it : CropDescCollection)
	{
		it.ID = element_id++;
	}
}

const bool AXLagCropManager::Empty() const
{
	return CropDescCollection.Num() == 0;
}

const FXLagCropDescription& AXLagCropManager::FindById(const int id) const
{
	return *CropDescCollection.FindByPredicate([id](auto& it) {return it.ID == id; });
}