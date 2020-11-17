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
	if (!Baggage->HasQuanity(XLagDynamicObjectType::Product, product, quanity))
	{
		Baggage->Put(XLagDynamicObjectType::Product, product, deltaTime);
		IsManualProduction = true;
	}
	else
	{
		Baggage->Reset(XLagDynamicObjectType::Product);
		Baggage->Put(XLagDynamicObjectType::Product, product, quanity);
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

		if (Baggage->Take(XLagDynamicObjectType::Product, product, 1) > 0.0f)
		{
			stack->AddQuantity(1.0);
		}
		else
		{
			IsProductPutting = false;
			Baggage->Reset(XLagDynamicObjectType::Product);
		}
	}

	return !IsProductPutting;
}

void AXLagNPCWorker::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}