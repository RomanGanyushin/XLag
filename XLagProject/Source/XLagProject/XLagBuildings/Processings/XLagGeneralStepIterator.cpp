#include "XLagGeneralStepIterator.h"

void FXLagGeneralStepIterator::SetEvaluator(FXLagBuildParameterEvaluator* evaluator)
{
	_evaluator = evaluator;
}

void FXLagGeneralStepIterator::SetGeneralPlain(const FGeneralPlain *generalPlain)
{
	GeneralPlain = generalPlain;
	BeginInitialize();
}

void FXLagGeneralStepIterator::BeginInitialize()
{
	if (GeneralPlain == nullptr || GeneralPlain->GeneralSteps.Num() == 0)
		return;

	InitializeNextGeneralStep();
}

const FGeneralStep* FXLagGeneralStepIterator::GetCurrentGeneralStep() const
{
	if (_generalStepIndex == -1)
		return nullptr;

	return &GeneralPlain->GeneralSteps[_generalStepIndex];
}

const FSubStep* FXLagGeneralStepIterator::GetCurrentSubStep() const
{
	auto generalStep = GetCurrentGeneralStep();
	if (generalStep == nullptr)
		return nullptr;

	auto stepId = generalStep->SubStepIds[_subStepIndex];
	return FindSubStepById(stepId);
}

void FXLagGeneralStepIterator::Next()
{
	NextSubStep();
}

void FXLagGeneralStepIterator::InitializeNextGeneralStep()
{
	auto currentGeneralStep = GetCurrentGeneralStep();

	if (currentGeneralStep != nullptr && !currentGeneralStep->Repeat.IsEmpty())
	{
		auto repateCount = _evaluator->EvaluateInt(currentGeneralStep->Repeat.Count);

		_generalStepCount++;
		if (repateCount > _generalStepCount)
		{
			_evaluator->SetParameter(TEXT("GeneralStepIndex"), FString::Printf(TEXT("%d"), _generalStepCount));
			_isNextGeneralCycleStep = true;	
			IntializeBeginSubStep();
			return;
		}
	}
	
	_generalStepCount = 0;
	_generalStepIndex++;
	_evaluator->SetParameter(TEXT("GeneralStepIndex"), FString::Printf(TEXT("%d"), _generalStepCount));
	
	if (GeneralPlain->GeneralSteps.Num() <= _generalStepIndex)
	{
		InitializeComplite();
	}
	else
	{
		_isNextGeneralSteps = true;
		IntializeBeginSubStep();
	}
}

void FXLagGeneralStepIterator::IntializeBeginSubStep()
{
	_subStepIndex = -1;
	NextSubStep();	
}

void FXLagGeneralStepIterator::NextSubStep()
{
	auto subStepIdsCount = GetCurrentGeneralStep()->SubStepIds.Num();
	FindNextSubStep();

	if (_subStepIndex >= subStepIdsCount)
	{
		InitializeNextGeneralStep();
		return;
	}
}


void FXLagGeneralStepIterator::FindNextSubStep()
{
	while (++_subStepIndex < GetCurrentGeneralStep()->SubStepIds.Num())
	{
		if (GetCurrentSubStep() != nullptr)
			break;
	}
}

void FXLagGeneralStepIterator::InitializeComplite()
{
	_generalStepIndex = -1;
	_subStepIndex = -1;
	_isComplete = true;
}


const FSubStep* FXLagGeneralStepIterator::FindSubStepById(const FString& stepId) const
{
	for (int i = 0; i < GeneralPlain->SubSteps.Num(); i++)
	{
		if (GeneralPlain->SubSteps[i].Id.Equals(stepId, ESearchCase::IgnoreCase))
		{
			return &GeneralPlain->SubSteps[i];
		}
	}

	return nullptr;
}