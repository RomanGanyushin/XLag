#pragma once

#include "../Models/GeneralPlain.h"
#include "XLagBuildParameterEvaluator.h"
#include "XLagBuildProcessing.generated.h"

UCLASS()
class UXLagBuildProcessing : public UClass
{
	GENERATED_UCLASS_BODY()

public:	
	void SetGeneralPlain(TSharedPtr<FGeneralPlain> generalPlain);
	void DoProcess(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate);

public:	
	UPROPERTY(BlueprintReadOnly) FString BuildingName;
private:
	UXLagBuildParameterEvaluator* Evaluator;
	TSharedPtr<FGeneralPlain> GeneralPlain;
	FGeneralStep *CurrentGeneralStep = nullptr;
	const FSubStep* FindSubStepById(const FString& stepId) const;

	void InitializePlain();
};