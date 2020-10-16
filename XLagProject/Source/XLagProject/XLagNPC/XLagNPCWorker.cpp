#include "XLagNPCWorker.h"

void AXLagNPCWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLagNPCWorker::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}
