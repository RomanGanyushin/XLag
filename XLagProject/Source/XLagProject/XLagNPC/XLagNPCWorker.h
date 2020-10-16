#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
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
	virtual void OfferAccept(UXLagTaskBase* task) override;

protected:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Worker; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }
};
