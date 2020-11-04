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
	IsMineralTaking = isReserved;

	return !IsMineralTaking;
}

bool AXLagNPCWorker::ManualProduction(FString product, float quanity, float deltaTime)
{
	if (!Bag.Has(product, quanity))
	{
		Bag.Put(product, deltaTime);
		IsManualProduction = true;
	}
	else
	{
		Bag.Reset();
		Bag.Put(product, quanity);
		IsManualProduction = false;
	}	

	return !IsManualProduction;
}

bool AXLagNPCWorker::PutProductAtStack(FString product, AXLagProductStack* stack, float deltaTime)
{
	static float timeAccamulator = 0;
	timeAccamulator += deltaTime;

	IsProductPutting = true;

	if (timeAccamulator > 2.0)
	{
		timeAccamulator = 0.0f;

		if (Bag.Take(product, 1) > 0.0f)
		{
			stack->AddQuantity(1.0);
		}
		else
		{
			IsProductPutting = false;
			Bag.Reset();
		}
	}

	return !IsProductPutting;
}

void AXLagNPCWorker::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}