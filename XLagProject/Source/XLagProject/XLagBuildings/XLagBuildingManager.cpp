#include "XLagBuildingManager.h"
#include "../XLagNPC/XLagNPCSwapManagement.h"
#include "Models/GeneralPlainSerialization.h"

AXLagBuildingManager::AXLagBuildingManager()
{
	CreateBuildingCollection();
}

const FXLagBuildingDescription& AXLagBuildingManager::GetSelectBuilding() const
{
	return _selectBuilding;
}

void AXLagBuildingManager::SetSelectBuilding(FXLagBuildingDescription select)
{
	_selectBuilding = select;	
	SetPreviewSelectBuilding(IsSelectBuilding);
}

bool AXLagBuildingManager::GetPreviewSelectBuilding() const
{
	return _isPreviewSelectBuilding;
}

void AXLagBuildingManager::SetPreviewSelectBuilding(const bool preview)
{
	if (_isPreviewSelectBuilding == preview)
		return;

	if (preview && 	_selectBuilding.IsExist)
	{
		CreatePreviewSelectBuilding();
	}
	else
	{
		DestroyPreviewSelectBuilding();
	}

	_isPreviewSelectBuilding = preview;
}

AXLagBuilding *AXLagBuildingManager::BuildingSiteFound(const FXLagBuildingDescription& building)
{
	auto swapManager = AXLagNPCSwapManagement::GetManagment();
	auto newBuilding = swapManager->DoSwapBuilding();
	auto position = MapAccessor->GetWorldPosition(building.PositionX, building.PositionY, GetPositionEnum::CenterHeghtPosition);
	newBuilding->SetActorLocation(position);
	newBuilding->SetGeneralPlain(&building.GetGeneralPlain());

	return newBuilding;
}

void AXLagBuildingManager::SetPreviewPosition(const float x, const float y)
{
	if (!_isPreviewSelectBuilding)
		return;

	if (_previewBuilding == nullptr)
		return;

	if (x == 0 && y == 0)
		return;

	auto newPositon = CoordinatePoint(x / 100, y / 100);
	auto oldPositon = CoordinatePoint(_selectBuilding.PositionX, _selectBuilding.PositionY);

	if (oldPositon.IsEqual(newPositon))
		return;

	_selectBuilding.PositionX = newPositon.X;
	_selectBuilding.PositionY = newPositon.Y;

	auto position = MapAccessor->GetWorldPosition(newPositon, GetPositionEnum::CenterHeghtPosition);
	_previewBuilding->SetActorLocation(position);
}

#pragma region Private Methods

void AXLagBuildingManager::CreateBuildingCollection()
{
	auto files = UGeneralPlainSerialization::ScanFiles();
	for (auto& file : files)
	{
		auto generalPlain = UGeneralPlainSerialization::LoadFromFile(file);
		if (generalPlain == nullptr)
			continue;

		auto plain = UGeneralPlainSerialization::LoadFromFile(file);
		auto& item = BuildingCollection.AddDefaulted_GetRef();
		item.SetGeneralPlain(*plain);
		delete plain;
	}
}

void AXLagBuildingManager::CreatePreviewSelectBuilding()
{
	auto swapManager = AXLagNPCSwapManagement::GetManagment();
	_previewBuilding = swapManager->DoSwapBuilding();
	_previewBuilding->SetGeneralPlain(&_selectBuilding.GetGeneralPlain());
	_previewBuilding->DoShowPreview(true);    
}

void AXLagBuildingManager::DestroyPreviewSelectBuilding()
{
	if (_previewBuilding == nullptr)
		return;

	GetWorld()->DestroyActor(_previewBuilding);
	_previewBuilding = nullptr;
}

#pragma endregion

