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
	void SetGeneralPlain(FGeneralPlain* generalPlain);
	void DoProcess(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate);

public:	
	UPROPERTY(BlueprintReadOnly) FString BuildingName;
private:
	FXLagBuildParameterEvaluator* Evaluator;
	UXLagGeneralStepIterator *GeneralStepIterator;
	FRepeatCycle* _repeatCycle;
	void GenerateParametersFrom(TArray<FBuildingElement> elements);
	void InitializeSubStep();
	void ExecuteRepeatCycle(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate);
	void SpawnBuildingElement(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate);
	void SetupPosition(const FPositionSetup* setup);
};