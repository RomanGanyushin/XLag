#include "XLagBuildParameterEvaluator.h"

UXLagBuildParameterEvaluator::UXLagBuildParameterEvaluator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

FVector UXLagBuildParameterEvaluator::Evaluate(const FUnboundedVector3& unbundedVector) const
{
	FVector result = FVector::ZeroVector;
	result.X = EvaluateFloat(unbundedVector.X);
	result.Y = EvaluateFloat(unbundedVector.Y);
	result.Z = EvaluateFloat(unbundedVector.Z);
	return result;
}

FRotator UXLagBuildParameterEvaluator::Evaluate(const FUnboundedRotator3& unbundedVector) const
{
	FRotator result = FRotator(0, 0, 0);
	result.Pitch = EvaluateFloat(unbundedVector.Pitch);
	result.Yaw = EvaluateFloat(unbundedVector.Yaw);
	result.Roll = EvaluateFloat(unbundedVector.Roll);
	return result;
}

const int32 UXLagBuildParameterEvaluator::EvaluateInt(const FString& numeric) const
{
	return numeric.IsEmpty() ? 0 : FCString::Atoi(*numeric);
}

const float UXLagBuildParameterEvaluator::EvaluateFloat(const FString& numeric) const
{
	return numeric.IsEmpty() ? 0.0 : FCString::Atof(*numeric);
}