#pragma once
#include "Math/BasicMathExpressionEvaluator.h"
#include "../Models/GeneralPlain.h"
#include "XLagBuildParameterEvaluator.generated.h"

USTRUCT()
struct FXLagBuildParameterEvaluator
{
	GENERATED_BODY()

public:
	FXLagBuildParameterEvaluator();
	FVector Evaluate(const FUnboundedVector3& unbundedVector) const;
	FRotator Evaluate(const FUnboundedRotator3& unbundedVector) const;
	const int32 EvaluateInt(const FString& numeric) const;
	const float EvaluateFloat(const FString& numeric) const;

	void ResetLocal(const FVector& local);
	void OffsetPosition(const FVector& offset);
	void ResetOrientation(const FRotator& rotator);
	void OffsetOrientation(const FRotator& offset);

	void SetParameter(FString name, FString value);
	void SetParameters(TArray<FXLagBuildParameter> params);
	FXLagBuildParameter* FindParameter(FString name);

	UPROPERTY() FVector CurrentPosition = FVector::ZeroVector;
	UPROPERTY() FRotator CurrentOrientation = FRotator::ZeroRotator;

private:
	TArray<FXLagBuildParameter*> _parameters;
	FBasicMathExpressionEvaluator* _mathEvaluator;
	const float CalculateValue(const FString numeric) const;
	const FString PatchParameters(const FString expression) const;
};