#pragma once
#include "GameFramework/Actor.h"
#include "Models/XLagCropDescription.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "../XLagDynamicObject/XLagDynamicObject.h"
#include "../XLagNPC/XLagSwapableObject.h"
#include "XLagCrop.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagCrop : public AXLagSwapableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXLagCrop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FXLagCropDescription Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentStage = 0;

	UPROPERTY(BlueprintReadOnly)
		UStaticMeshComponent *CurrentMeshComponent;

	UPROPERTY(BlueprintReadOnly)
		float Progression = 0;

	void Initialize(FXLagCropDescription description);

	void AssignObject(const FXLagDynamicObject& object) override;

protected:
	UFUNCTION()
	void OnPropertyChanged(uint8 id, const FXLagObjectProperties& properties);

private:
	bool IsVaild() const;
	const FXLagCropStage* GetCurrentStage() const;
	void UpdateView();
	void UpdateStageView();
	void NextStage();
	void CreateStageView();
	void DestroyStageView();
	float GetLocalStageProgression() const;
};