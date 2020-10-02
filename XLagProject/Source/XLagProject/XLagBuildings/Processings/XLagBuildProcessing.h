#pragma once

#include "../Models/GeneralPlain.h"
#include "XLagBuildParameterEvaluator.h"
#include "XLagGeneralStepIterator.h"
#include "XLagBuildProcessing.generated.h"

USTRUCT()
struct FRepeatCycle
{
	GENERATED_BODY()
	int32 Index = 0;
	int32 Count = 0;
	FVector IncrementalPosition;
	FRotator IncrementalRotator;
};

UCLASS()
class UXLagBuildProcessing : public UClass
{
	GENERATED_UCLASS_BODY()

public:	
	void SetGeneralPlain(const FGeneralPlain* generalPlain);
	void DoProcess(UObject* owner, USceneComponent*root);
	void CreatePreview(UObject* owner, USceneComponent*root);
	bool IsComplite() const;
public:	
	UPROPERTY(BlueprintReadOnly) FString BuildingName;
private:
	const FGeneralPlain* GeneralPlain;
	FXLagBuildParameterEvaluator* Evaluator;
	FXLagGeneralStepIterator GeneralStepIterator;
	FRepeatCycle* _repeatCycle;
	void GenerateParametersFrom(TArray<FBuildingElement> elements);
	void InitializeSubStep();
	void ExecuteRepeatCycle(UObject* owner, USceneComponent* root);
	void SpawnBuildingElement(UObject* owner, USceneComponent* root);
	void SetupPosition(const FPositionSetup* setup);

	bool isPreviewMode = false;
};