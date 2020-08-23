#include "XLagBuildParameterEvaluator.h"

FXLagBuildParameterEvaluator::FXLagBuildParameterEvaluator()
{
	_mathEvaluator = new FBasicMathExpressionEvaluator();
}

void FXLagBuildParameterEvaluator::SetParameter(FString name, FString value)
{
	auto parameter = FindParameter(name);
	if (parameter == nullptr)
	{
		auto newParameter = new FXLagBuildParameter();
		newParameter->Value = FString::Printf(TEXT("%s"), *value);
		newParameter->Name = FString::Printf(TEXT("%s"), *name);
		_parameters.Add(newParameter);
	}
	else
	{
		parameter->Value = value;
	}
}

void FXLagBuildParameterEvaluator::SetParameters(TArray<FXLagBuildParameter> params)
{
	for (auto& it : params)
		SetParameter(it.Name, it.Value);
}

FXLagBuildParameter* FXLagBuildParameterEvaluator::FindParameter(FString name)
{
	for (auto &it : _parameters)
	{
		if (it->Name.Equals(name, ESearchCase::IgnoreCase))
		{
			return it;
		}
	}

	return nullptr;
}

FVector FXLagBuildParameterEvaluator::Evaluate(const FUnboundedVector3& unbundedVector) const
{
	FVector result = FVector::ZeroVector;
	result.X = EvaluateFloat(unbundedVector.X);
	result.Y = EvaluateFloat(unbundedVector.Y);
	result.Z = EvaluateFloat(unbundedVector.Z);
	return result;
}

FRotator FXLagBuildParameterEvaluator::Evaluate(const FUnboundedRotator3& unbundedVector) const
{
	FRotator result = FRotator(0, 0, 0);
	result.Pitch = EvaluateFloat(unbundedVector.Pitch);
	result.Yaw = EvaluateFloat(unbundedVector.Yaw);
	result.Roll = EvaluateFloat(unbundedVector.Roll);
	return result;
}

double FXLagBuildParameterEvaluator::Evaluate(const FString& arg) const
{
	return EvaluateFloat(arg);
}

const int32 FXLagBuildParameterEvaluator::EvaluateInt(const FString& numeric) const
{
	return (int32)CalculateValue(numeric);
}

const float FXLagBuildParameterEvaluator::EvaluateFloat(const FString& numeric) const
{
	return CalculateValue(numeric);
}

void FXLagBuildParameterEvaluator::ResetLocal(const FVector& local)
{
	CurrentPosition = local;
}

void FXLagBuildParameterEvaluator::OffsetPosition(const FVector& offset)
{
	CurrentPosition += offset;
}

void FXLagBuildParameterEvaluator::ResetOrientation(const FRotator& rotator)
{
	CurrentOrientation = rotator;
}
void FXLagBuildParameterEvaluator::OffsetOrientation(const FRotator& offset)
{
	CurrentOrientation += offset;
}

const float FXLagBuildParameterEvaluator::CalculateValue(const FString numeric) const
{
	if (numeric.IsEmpty())
		return 0;

	if (numeric.IsNumeric())
		return FCString::Atoi(*numeric);

	auto prepared = PatchParameters(numeric);
	auto calculated = _mathEvaluator->Evaluate(*prepared);

	if (calculated.IsValid())
	{
		return calculated.GetValue();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UXLagBuildParameterEvaluator. Expression error: %s"), *numeric);
	}

	return 0.0;
}

const FString FXLagBuildParameterEvaluator::PatchParameters(const FString expression) const
{
	FString result = expression;
	
	for (auto &it : _parameters)
	{
		result = result.Replace(*it->NameInExpression(), *it->Value, ESearchCase::IgnoreCase);
	}

	return result;
}