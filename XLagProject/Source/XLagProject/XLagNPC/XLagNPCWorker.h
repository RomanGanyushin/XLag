#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "XLagMineralStack.h"
#include "XLagProductStack.h"
#include "XLagNPCWorker.generated.h"

/**
 *
 */
UCLASS()
class XLAGPROJECT_API AXLagNPCWorker : public AXLagNPCBase
{
	GENERATED_BODY()

		// Called every frame
		virtual void Tick(float DeltaTime) override;

public:	
	bool TakeReservedMineral(AXLagMineralStack* stack, float deltaTime);
	bool ManualProduction(FString product, float quanity, float deltaTime);
	bool PutProductAtStack(FString product, AXLagProductStack* stack, float quanity, float deltaTime);
	virtual void OfferAccept(UXLagTaskBase* task) override;
	
protected:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Worker; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }
};
