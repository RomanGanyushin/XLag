#include "XLagNPCWorker.h"

void AXLagNPCWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AXLagNPCWorker::TakeReservedMineral(AXLagMineralStack* stack, float deltaTime)
{
	float takeForce = deltaTime;
	stack->TakeQuantity(this, takeForce);

	auto isReserved = stack->IsReservedFor(this);
	return !isReserved;
}

bool AXLagNPCWorker::ManualProduction(FString product, float quanity, float deltaTime)
{
	if (!Bag.Has(TCHAR_TO_UTF8(*product), quanity))
	{
		Bag.Put(TCHAR_TO_UTF8(*product), deltaTime);
		return false;
	}
	else
	{
		Bag.Reset();
		Bag.Put(TCHAR_TO_UTF8(*product), quanity);
		return true;
	}	
}

bool AXLagNPCWorker::PutProductAtStack(FString product, AXLagProductStack* stack, float quanity, float deltaTime)
{
	Bag.Reset();
	stack->AddQuantity(quanity);
	return true;
}

void AXLagNPCWorker::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}