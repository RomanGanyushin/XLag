#include "XLagNPCFarmer.h"
#include "XLagNPCSwapManagement.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"
#include "../Common/CellOperationProcessing.h"

#define DEBUG_FORCE_MULTIPLIER 1

void AXLagNPCFarmer::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}


bool AXLagNPCFarmer::Plough(FXLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto force = DeltaTime;
	auto plough = force * DEBUG_FORCE_MULTIPLIER;

	auto isComplite = false;
	auto currentTopKind = XLagDynamicTerrainMapItemOperation(cell).GetTopKind();

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
			XLagDynamicTerrainMapItemOperation(cell).Pour(plough, TerrainElementEnum::Cultivated);
		}
	}
	else
	{
		XLagDynamicTerrainMapItemOperation(cell).Pour(plough, TerrainElementEnum::Cultivated);
	}

	isComplite = XLagDynamicTerrainMapItemOperation(cell).GetHeghtTopLevel() > 10;
	IsPloughing = !isComplite;

	return isComplite;
}

bool AXLagNPCFarmer::Sow(FXLagDynamicTerrainMapItem& cell, const FXLagCropDescription& crop, float DeltaTime)
{
	auto force = DeltaTime;
	auto sowForce = force * DEBUG_FORCE_MULTIPLIER;

	auto isComplite = false;
	
	if (!ValidateForSowCell(cell))
	{
		isComplite = true;
		IsSowing = false;
		return true;
	}

	if (cell.OnSurfaceResourceObjects == OnSurfaceResourceObjectsEnum::Empty)
	{
		CellOperationProcessing operation(&cell, CellOperationEnum::Sow, 5);
		operation.Increase(sowForce);
		
		if (!operation.IsComplete())
		{
			isComplite = false;
			IsSowing = true;
		}
		else
		{
			isComplite = true;
			IsSowing = false;
			cell.OperationTimeMap.Remove(CellOperationEnum::Sow);

			cell.OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Crop;
			auto swapManager = AXLagNPCSwapManagement::GetManagment(); // Переделать через менеджер
			swapManager->DoSwapCrop(cell, crop);

			CellOperationProcessing evolutionTime(&cell, CellOperationEnum::EvolutionTime);
			evolutionTime.Set(crop.TimeLife);
		}
	}

	return isComplite;
}

bool AXLagNPCFarmer::Grow(FXLagDynamicTerrainMapItem& cell, float DeltaTime)
{
	auto force = DeltaTime;
	auto growForce = force * DEBUG_FORCE_MULTIPLIER;

	auto isComplite = false;

	if (!ValidateForGrowCell(cell))
	{
		isComplite = true;
		IsGrowing = false;
		return true;
	}

	CellOperationProcessing operation(&cell, CellOperationEnum::Grow, 5);
	operation.Increase(growForce);

	if (!operation.IsComplete())
	{
		isComplite = false;
		IsGrowing = true;
	}
	else
	{
		isComplite = true;
		IsGrowing = false;
		cell.OperationTimeMap.Remove(CellOperationEnum::Grow);
	}

	return isComplite;
}

bool AXLagNPCFarmer::TakeCrop(FXLagDynamicTerrainMapItem& cell, float DeltaTime)
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

	isComplite = operation.IsEmpty();
	IsHarvesting = !isComplite;

	if (isComplite)
	{
		auto swapManager = AXLagNPCSwapManagement::GetManagment(); // Переделать через менеджер
		swapManager->DoUnswapCrop(cell);
		CellOperationProcessing(&cell, CellOperationEnum::Grow).Reset(); 
		CellOperationProcessing(&cell, CellOperationEnum::Sow).Reset();
		CellOperationProcessing(&cell, CellOperationEnum::Evolution).Reset();
		cell.OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Empty;
	}
	
	return isComplite;
}

bool AXLagNPCFarmer::ValidateForSowCell(FXLagDynamicTerrainMapItem& cell)
{
	auto currentTopKind = XLagDynamicTerrainMapItemOperation(cell).GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
		return false;

	if (cell.OnSurfaceResourceObjects != OnSurfaceResourceObjectsEnum::Empty &&
		cell.OnSurfaceResourceObjects != OnSurfaceResourceObjectsEnum::Crop)
		return false;

	return true;
}

bool AXLagNPCFarmer::ValidateForGrowCell(FXLagDynamicTerrainMapItem& cell)
{
	auto currentTopKind = XLagDynamicTerrainMapItemOperation(cell).GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
		return false;

	if (cell.OnSurfaceResourceObjects != OnSurfaceResourceObjectsEnum::Crop)
		return false;

	return true;
}

bool AXLagNPCFarmer::ValidateForTakeCropCell(FXLagDynamicTerrainMapItem& cell)
{
	if (!ValidateForGrowCell(cell))
		return false;

	CellOperationProcessing operation(&cell, CellOperationEnum::CropQuantity);
	return !operation.IsEmpty();
}