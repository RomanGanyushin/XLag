#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagCrops/XLagCropManager.h"
#include "XLagNPCFarmer.generated.h"

/**
 *
 */
UCLASS()
class XLAGPROJECT_API AXLagNPCFarmer : public AXLagNPCBase
{
	GENERATED_BODY()

public:
	virtual void OfferAccept(UXLagTaskBase* task) override;

	// ������� ������.
	virtual bool Plough(FXLagDynamicTerrainMapItem& cell, float DeltaTime);

	// ����� ������.
	virtual bool Sow(FXLagDynamicTerrainMapItem& cell, const int32 cropId, float DeltaTime);

	// ���������� (���������, ��������)
	virtual bool Grow(FXLagDynamicTerrainMapItem& cell, float DeltaTime);

	// �������� ������.
	virtual bool TakeCrop(FXLagDynamicTerrainMapItem& cell, float DeltaTime);

	// ����� ������.
	virtual bool SearchStack(int32 cropId);

	// �������� ������ � ������.
	virtual bool PutCropToStack(float DeltaTime);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsPloughing = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsSowing = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsGrowing = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsHarvesting = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Farmer Working")
		bool  IsDischarging = false;

private:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Farmer; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }

private:
	bool ValidateForSowCell(FXLagDynamicTerrainMapItem& cell);
	bool ValidateForGrowCell(FXLagDynamicTerrainMapItem& cell);
	bool ValidateForTakeCropCell(FXLagDynamicTerrainMapItem& cell);
};
