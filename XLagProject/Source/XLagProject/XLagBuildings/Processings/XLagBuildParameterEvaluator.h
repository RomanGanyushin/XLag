#pragma once
#include "Math/BasicMathExpressionEvaluator.h"
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

	void ResetLocal(const FVector& local);
	void OffsetPosition(const FVector& offset);
	void ResetOrientation(const FRotator& rotator);
	void OffsetOrientation(const FRotator& offset);

	UPROPERTY() FVector CurrentPosition = FVector::ZeroVector;
	UPROPERTY() FRotator CurrentOrientation = FRotator::ZeroRotator;

private:
	TSharedPtr<FBasicMathExpressionEvaluator> _mathEvaluator;
};