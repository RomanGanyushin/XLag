#pragma once
#include "GameFramework/Actor.h"
#include "Models/XLagCropDescription.h"
#include "XLagCrop.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagCrop : public AActor
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
		float LocalTime = 0;

	void Initialize(FXLagCropDescription description);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool IsVaild() const;
	const FXLagCropStage* GetCurrentStage() const;
	void UpdateView();
	void UpdateStageView();
	void NextStage();
	void CreateStageView();
	void DestroyStageView();
	float GetLocalStageTime() const;
};