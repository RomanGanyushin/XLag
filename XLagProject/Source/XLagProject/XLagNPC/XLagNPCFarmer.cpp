#include "XLagNPCFarmer.h"
#include "XLagNPCSwapManagement.h"

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
	
	if (!ValidateCell(cell))
	{
		isComplite = true;
		IsSowing = false;
		return true;
	}

	if (cell.OnSurfaceResourceObjects == OnSurfaceResourceObjectsEnum::Empty)
	{
		if (cell.OperationTimeMap.find(0) == cell.OperationTimeMap.end())
		{
			cell.OperationTimeMap[0] = 0.0f;
		}
		else
		{
			cell.OperationTimeMap[0] += sowForce;
		}

		if (cell.OperationTimeMap[0] < 5.0)
		{
			isComplite = false;
			IsSowing = true;
		}
		else
		{
			isComplite = true;
			IsSowing = false;
			cell.OperationTimeMap.erase(0);

			cell.OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Crop;
			auto swapManager = AXLagNPCSwapManagement::GetManagment(); // Переделать через менеджер
			swapManager->DoSwapCrop(cell, crop);
		}
	}

	return isComplite;
}

bool AXLagNPCFarmer::ValidateCell(XLagDynamicTerrainMapItem& cell)
{
	auto currentTopKind = cell.GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
		return false;

	if (cell.OnSurfaceResourceObjects != OnSurfaceResourceObjectsEnum::Empty &&
		cell.OnSurfaceResourceObjects != OnSurfaceResourceObjectsEnum::Crop)
		return false;

	return true;
}