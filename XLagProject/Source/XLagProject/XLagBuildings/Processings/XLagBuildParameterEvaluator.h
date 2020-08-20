#pragma once
#include "../Models/GeneralPlain.h"

#include "XLagBuildParameterEvaluator.generated.h"

UCLASS()
class UXLagBuildParameterEvaluator : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	FVector Evaluate(const FUnboundedVector3& unbundedVector) const;
	FRotator Evaluate(const FUnboundedRotator3& unbundedVector) const;
	const int32 EvaluateInt(const FString& numeric) const;
	const float EvaluateFloat(const FString& numeric) const;
};