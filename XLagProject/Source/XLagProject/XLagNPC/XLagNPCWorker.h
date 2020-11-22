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
		bool  IsMineralWaiting = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Worker Working")
		bool  IsMineralTaking = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Worker Working")
		bool  IsManualProduction = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Worker Working")
		bool  IsDischarging = false;


	/// Найти и зарезервироать минералы из кучи.
	bool SearchAndReserveMineralStack(const int mineralId, const float quanity);

	/// Получить зарезервированный материал из кучи.
	bool TakeReservedMineral(float deltaTime, const float totalQuanity);

	/// Ручное производство.
	bool ManualProduction(const int32 productId, float quanity, float deltaTime);

	/// Найти стопку для продукта.
	bool SearchProductStack(int32 productId);

	/// Положить произведенный продукт к стопку. 
	bool PutProductAtStack(const int32 productId, float deltaTime);

	virtual void OfferAccept(UXLagTaskBase* task) override;
	
protected:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Worker; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }
};
