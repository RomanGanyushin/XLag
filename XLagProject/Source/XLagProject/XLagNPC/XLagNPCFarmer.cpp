#include "XLagNPCFarmer.h"
#include "XLagNPCSwapManagement.h"
#include "../Common/CellOperationProcessing.h"

void AXLagNPCFarmer::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}


bool AXLagNPCFarmer::Plough(XLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto force = DeltaTime;
	auto plough = force;

	auto isComplite = false;
	auto currentTopKind = cell.GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
	{
		if (currentTopKind != TerrainElementEnum::GraundGrass && // Это не совсем правильно. Надо более стабильный признак
			currentTopKind != TerrainElementEnum::GrondGrassToCultivatedTrans) 
		{
			isComplite = true;
			IsPloughing = false;
			return true;
		}
		else
		{
			cell.Pour(plough, TerrainElementEnum::Cultivated);
		}
	}
	else
	{
		cell.Pour(plough, TerrainElementEnum::Cultivated);
	}

	isComplite = cell.GetHeghtTopLevel() > 10;
	IsPloughing = !isComplite;

	return isComplite;
}

bool AXLagNPCFarmer::Sow(XLagDynamicTerrainMapItem& cell, const FXLagCropDescription& crop, float DeltaTime)
{
	auto force = DeltaTime;
	auto sowForce = force;

	auto isComplite = false;
	
	if (!ValidateForSowCell(cell))
	{
		isComplite = true;
		IsSowing = false;
		return true;
	}

	if (cell.OnSurfaceResourceObjects == OnSurfaceResourceObjectsEnum::Empty)
	{
		if (cell.OperationTimeMap.find(CellOperationEnum::Sow) == cell.OperationTimeMap.end())
		{
			cell.OperationTimeMap[CellOperationEnum::Sow] = 0.0f;
		}
		else
		{
			cell.OperationTimeMap[CellOperationEnum::Sow] += sowForce;
		}

		if (cell.OperationTimeMap[CellOperationEnum::Sow] < 5.0)
		{
			isComplite = false;
			IsSowing = true;
		}
		else
		{
			isComplite = true;
			IsSowing = false;
			cell.OperationTimeMap.erase(CellOperationEnum::Sow);

			cell.OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Crop;
			auto swapManager = AXLagNPCSwapManagement::GetManagment(); // Переделать через менеджер
			swapManager->DoSwapCrop(cell, crop);
		}
	}

	return isComplite;
}

bool AXLagNPCFarmer::Grow(XLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto force = DeltaTime;
	auto sowForce = force;

	auto isComplite = false;

	if (!ValidateForGrowCell(cell))
	{
		isComplite = true;
		IsGrowing = false;
		return true;
	}

	if (cell.OperationTimeMap.find(CellOperationEnum::Grow) == cell.OperationTimeMap.end())
	{
		cell.OperationTimeMap[CellOperationEnum::Grow] = 0.0f;
	}
	else
	{
		cell.OperationTimeMap[CellOperationEnum::Grow] += sowForce;
	}

	if (cell.OperationTimeMap[CellOperationEnum::Grow] < 5.0)
	{
		isComplite = false;
		IsGrowing = true;
	}
	else
	{
		isComplite = true;
		IsGrowing = false;
		cell.OperationTimeMap.erase(CellOperationEnum::Grow);
	}

	return isComplite;
}

bool AXLagNPCFarmer::TakeCrop(XLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto force = DeltaTime;
	auto takeForce = force;

	auto isComplite = false;

	if (!ValidateForTakeCropCell(cell))
	{
		isComplite = true;
		IsHarvesting = false;
		return true;
	}

	CellOperationProcessing operation(&cell, CellOperationEnum::CropQuantity);
	auto takeQuantity = operation.Decrease(takeForce);
	CollectedCropQuantity += takeQuantity;

	IsHarvesting = !isComplite;
	isComplite = operation.IsEmpty();

	return isComplite;
}

bool AXLagNPCFarmer::ValidateForSowCell(XLagDynamicTerrainMapItem& cell)
{
	auto currentTopKind = cell.GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
		return false;

	if (cell.OnSurfaceResourceObjects != OnSurfaceResourceObjectsEnum::Empty &&
		cell.OnSurfaceResourceObjects != OnSurfaceResourceObjectsEnum::Crop)
		return false;

	return true;
}

bool AXLagNPCFarmer::ValidateForGrowCell(XLagDynamicTerrainMapItem& cell)
{
	auto currentTopKind = cell.GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
		return false;

	if (cell.OnSurfaceResourceObjects != OnSurfaceResourceObjectsEnum::Crop)
		return false;

	return true;
}

bool AXLagNPCFarmer::ValidateForTakeCropCell(XLagDynamicTerrainMapItem& cell)
{
	if (!ValidateForGrowCell(cell))
		return false;

	CellOperationProcessing operation(&cell, CellOperationEnum::CropQuantity);
	return !operation.IsEmpty();
}