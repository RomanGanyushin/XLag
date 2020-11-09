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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Worker Working")
		bool  IsMineralTaking = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Worker Working")
		bool  IsManualProduction = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Worker Working")
		bool  IsProductPutting = false;

	/// Получить зарезервированный материал из кучи.
	bool TakeReservedMineral(AXLagMineralStack* stack, float deltaTime);

	/// Ручное производство.
	bool ManualProduction(FString product, float quanity, float deltaTime);

	/// Положить произведенный продукт к стопку. 
	bool PutProductAtStack(FString product, AXLagProductStack* stack, float deltaTime);

	virtual void OfferAccept(UXLagTaskBase* task) override;
	
protected:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Worker; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }
};
