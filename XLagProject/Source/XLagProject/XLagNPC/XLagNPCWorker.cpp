#include "XLagNPCWorker.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"
#include "../Common/CellOperationProcessing.h"
#include "../XLagDynamicObject/ObjectModels/TerrainLooseStackObject.h"
#include "../XLagDynamicTerrainBase.h"
#include "../XLagDynamicTerrain\Position\RandomizeZeroPlacePosition.h"

void AXLagNPCWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AXLagNPCWorker::SearchAndReserveMineralStack(const int mineralId, const float quanity)
{
	auto& objects = AXLagDynamicObjectsManager::GetManagment()->GetObjects();
	auto mineralStacks = objects.GetFilteredByType(XLagDynamicObjectType::MineralStack);

	auto searchCondition = [mineralId, quanity](auto it)
	{
		TerrainMineralStackObject stackProperties(*it);
		return stackProperties.GetKind() == mineralId && stackProperties.GetStackQuantity() >= quanity;
	};

	auto searchingStack = mineralStacks.FindByPredicate(searchCondition);
	if (searchingStack == nullptr)
	{
		IsMineralWaiting = true;
		return false;
	}

	// TODO_ONE: Тут нужно зарезервировать в куче.
	FindCellIndex = (*searchingStack)->BindedMapItemIndexes[0];
	IsMineralWaiting = false;
	return true;
}

bool AXLagNPCWorker::TakeReservedMineral(float deltaTime, const float totalQuanity)
{
	float takeForce = deltaTime;

	auto terrain = AXLagDynamicTerrainBase::GetDynamicTerrainBase();
	auto& cell = terrain->Map->Point(FindCellIndex);

	XLagDynamicTerrainMapItemOperation cellOperation(cell);
	if (!cellOperation.HasObjectType(XLagDynamicObjectType::MineralStack))
	{
		IsMineralTaking = false;
		return true;
	}

	auto object = cellOperation.GetObjectByType(XLagDynamicObjectType::MineralStack);
	TerrainMineralStackObject mineralStackObjectProperty(*object);

	auto mineralId = mineralStackObjectProperty.GetKind();
	auto currentMineralQuantity = mineralStackObjectProperty.GetStackQuantity();
	auto takeQuantity = std::min(currentMineralQuantity, takeForce);
	
	if (takeQuantity == 0.0)
	{
		IsMineralTaking = false;
		return false;
	}
			
	mineralStackObjectProperty.SetStackQuantity(currentMineralQuantity - takeQuantity);

	Baggage->Put(XLagDynamicObjectType::Mineral, mineralId, takeQuantity);
	auto isSuccess = Baggage->HasQuanity(XLagDynamicObjectType::Mineral, mineralId, totalQuanity);
	IsMineralTaking = !isSuccess;

	return isSuccess;
}

bool AXLagNPCWorker::ManualProduction(const int32 productId, float quanity, float deltaTime)
{
	if (!Baggage->HasQuanity(XLagDynamicObjectType::Product, productId, quanity))
	{
		Baggage->Put(XLagDynamicObjectType::Product, productId, deltaTime);
		IsManualProduction = true;
	}
	else
	{
		Baggage->Reset(XLagDynamicObjectType::Product);
		Baggage->Put(XLagDynamicObjectType::Product, productId, quanity);
		IsManualProduction = false;
	}	

	return !IsManualProduction;
}

bool AXLagNPCWorker::SearchProductStack(int32 productId)
{
	auto& objects = AXLagDynamicObjectsManager::GetManagment()->GetObjects();
	auto productStacks = objects.GetFilteredByType(XLagDynamicObjectType::ProductStack);

	auto searchCondition = [productId](auto it)
	{
		TerrainProductStackObject stackProperties(*it);
		return stackProperties.GetKind() == productId;
	};

	auto searchingStack = productStacks.FindByPredicate(searchCondition);

	if (searchingStack == nullptr) // Если стопки нет, то создаем.
	{
		auto terrain = AXLagDynamicTerrainBase::GetDynamicTerrainBase();
		auto cell = RandomizeZeroPlacePosition(terrain->Map).GetCell();

		FXLagDynamicObject stackObject;
		stackObject.ObjectType = XLagDynamicObjectType::ProductStack;
		stackObject.BindedMapItemIndexes.Add(cell->Index);

		TerrainProductStackObject stackProperties(stackObject);
		stackProperties.SetKind(productId);
		objects.AddObject(stackObject);

		FindCellIndex = cell->Index;
	}
	else
	{
		FindCellIndex = (*searchingStack)->BindedMapItemIndexes[0];
	}

	return true;
}

bool AXLagNPCWorker::PutProductAtStack(const int32 productId, float deltaTime)
{
	static float timeAccamulator = 0;
	timeAccamulator += deltaTime;

	auto terrain = AXLagDynamicTerrainBase::GetDynamicTerrainBase();
	auto& cell = terrain->Map->Point(FindCellIndex);

	XLagDynamicTerrainMapItemOperation cellOperation(cell);
	if (!cellOperation.HasObjectType(XLagDynamicObjectType::ProductStack))
	{
		IsDischarging = false;
		return true;
	}

	auto object = cellOperation.GetObjectByType(XLagDynamicObjectType::ProductStack);
	TerrainProductStackObject productStackObjectProperty(*object);

	auto getFromBaggageProductQuantity = Baggage->Take(XLagDynamicObjectType::Product, productId, 1);

	if (getFromBaggageProductQuantity == 0.0f)
	{
		IsDischarging = false;
		return true;
	}

	productStackObjectProperty.SetStackQuantity(productStackObjectProperty.GetStackQuantity() + getFromBaggageProductQuantity);

	IsDischarging = true;
	return false;
}

void AXLagNPCWorker::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}