#include "XLagNPCFarmer.h"
#include "XLagNPCSwapManagement.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"
#include "../XLagDynamicObject/ObjectModels/TerrainCropObject.h"
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
		if (currentTopKind != TerrainElementEnum::GraundGrass && // ��� �� ������ ���������. ���� ����� ���������� �������
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

	XLagDynamicTerrainMapItemOperation cellOperation(cell);

	if (!ValidateForSowCell(cell))
	{
		isComplite = true;
		IsSowing = false;
		return true;
	}

	if (cellOperation.IsNoObjects())
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
			operation.Delete();

			FXLagDynamicObject cropObject;
			cropObject.ObjectType = XLagDynamicObjectType::Crop;
			cropObject.BindedMapItemIndexes.Add(cell.Index);
			
			TerrainCropObject cropProperties(cropObject);
			cropProperties.SetKind(crop.ID);
			cropProperties.SetLifetime(crop.TimeLife);

			cellOperation.AddObject(cropObject);
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
		operation.Delete();
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

	XLagDynamicTerrainMapItemOperation operationCell(cell);
	auto cropObject = operationCell.GetObjectByType(XLagDynamicObjectType::Crop);
	if (cropObject == nullptr)
		return false;

	TerrainCropObject cropProperties(*cropObject);
	auto quanity = cropProperties.GetCropQuantity();
	auto takeQuantity = std::min(quanity, takeForce);
	cropProperties.SetCropQuantity(quanity - takeQuantity);
	
	CollectedCropQuantity += takeQuantity;

	isComplite = cropProperties.GetCropQuantity() == 0.0f;

	IsHarvesting = !isComplite;

	if (isComplite)
	{
		operationCell.DeleteObject(cropObject);
		CellOperationProcessing(&cell, CellOperationEnum::Grow).Reset(); 
		CellOperationProcessing(&cell, CellOperationEnum::Sow).Reset();
	}
	
	return isComplite;
}

bool AXLagNPCFarmer::ValidateForSowCell(FXLagDynamicTerrainMapItem& cell)
{
	XLagDynamicTerrainMapItemOperation operationCell(cell);

	auto currentTopKind = operationCell.GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
		return false;

	return operationCell.IsNoObjects() || operationCell.HasObjectType(XLagDynamicObjectType::Crop);
}

bool AXLagNPCFarmer::ValidateForGrowCell(FXLagDynamicTerrainMapItem& cell)
{
	XLagDynamicTerrainMapItemOperation operationCell(cell);
	auto currentTopKind = operationCell.GetTopKind();

	if (currentTopKind != TerrainElementEnum::Cultivated)
		return false;

	return operationCell.HasObjectType(XLagDynamicObjectType::Crop);
}

bool AXLagNPCFarmer::ValidateForTakeCropCell(FXLagDynamicTerrainMapItem& cell)
{
	if (!ValidateForGrowCell(cell))
		return false;

	XLagDynamicTerrainMapItemOperation operationCell(cell);
	auto cropObject = operationCell.GetObjectByType(XLagDynamicObjectType::Crop);
	if (cropObject == nullptr)
		return false;
	 
	TerrainCropObject cropProperties(*cropObject);
	return cropProperties.GetCropQuantity() > 0.0f;
}