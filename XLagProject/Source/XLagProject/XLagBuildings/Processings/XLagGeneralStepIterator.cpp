#include "XLagGeneralStepIterator.h"

UXLagGeneralStepIterator::UXLagGeneralStepIterator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UXLagGeneralStepIterator::SetEvaluator(UXLagBuildParameterEvaluator* evaluator)
{
	_evaluator = evaluator;
}

void UXLagGeneralStepIterator::SetGeneralPlain(FGeneralPlain *generalPlain)
{
	GeneralPlain = generalPlain;
	BeginInitialize();
}

void UXLagGeneralStepIterator::BeginInitialize()
{
	if (GeneralPlain == nullptr || GeneralPlain->GeneralSteps.Num() == 0)
		return;

	InitializeNextGeneralStep();
}

const FGeneralStep* UXLagGeneralStepIterator::GetCurrentGeneralStep() const
{
	if (_generalStepIndex == -1)
		return nullptr;

	return &GeneralPlain->GeneralSteps[_generalStepIndex];
}

const FSubStep* UXLagGeneralStepIterator::GetCurrentSubStep() const
{
	auto generalStep = GetCurrentGeneralStep();
	if (generalStep == nullptr)
		return nullptr;

	auto stepId = generalStep->SubStepIds[_subStepIndex];
	return FindSubStepById(stepId);
}

void UXLagGeneralStepIterator::Next()
{
	NextSubStep();
}


void UXLagGeneralStepIterator::InitializeBeginGeneralStep()
{
	if (GeneralPlain->GeneralSteps.Num() == 0)
	{
		InitializeComplite();
		return;
	}

	_generalStepIndex = 0;
	IntializeBeginSubStep();
}

void UXLagGeneralStepIterator::InitializeNextGeneralStep()
{
	auto currentGeneralStep = GetCurrentGeneralStep();

	if (currentGeneralStep != nullptr && !currentGeneralStep->Repeat.IsEmpty())
	{
		auto repateCount = _evaluator->EvaluateInt(currentGeneralStep->Repeat.Count);

		if (repateCount > _generalStepCount)
		{
			_generalStepCount++;
			_isNextGeneralCycleStep = true;
			IntializeBeginSubStep();
			return;
		}
	}
	
	_generalStepCount = 0;
	_generalStepIndex++;
	
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

void UXLagGeneralStepIterator::IntializeBeginSubStep()
{
	_subStepIndex = -1;
	NextSubStep();	
}

void UXLagGeneralStepIterator::NextSubStep()
{
	auto subStepIdsCount = GetCurrentGeneralStep()->SubStepIds.Num();
	FindNextSubStep();

	if (_subStepIndex >= subStepIdsCount)
	{
		InitializeNextGeneralStep();
		return;
	}
}


void UXLagGeneralStepIterator::FindNextSubStep()
{
	while (++_subStepIndex < GetCurrentGeneralStep()->SubStepIds.Num())
	{
		if (GetCurrentSubStep() != nullptr)
			break;
	}
}

void UXLagGeneralStepIterator::InitializeComplite()
{
	_generalStepIndex = -1;
	_subStepIndex = -1;
	_isComplete = true;
}


const FSubStep* UXLagGeneralStepIterator::FindSubStepById(const FString& stepId) const
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