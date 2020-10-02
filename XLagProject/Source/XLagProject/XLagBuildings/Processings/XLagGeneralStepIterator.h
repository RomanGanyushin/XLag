#pragma once
#include "../Models/GeneralPlain.h"
#include "XLagBuildParameterEvaluator.h"
#include "XLagGeneralStepIterator.generated.h"

USTRUCT()
struct FXLagGeneralStepIterator
{
	GENERATED_BODY()

public:
	void SetEvaluator(FXLagBuildParameterEvaluator* evaluator);
	void SetGeneralPlain(const FGeneralPlain *generalPlain);

	const FGeneralStep* GetCurrentGeneralStep() const;
	const FSubStep* GetCurrentSubStep() const;
	const bool IsNewGeneralStep() const { return _isNextGeneralSteps; }
	const bool IsNextGeneralCycleStep() const { return _isNextGeneralCycleStep; }
	void Confirm() { _isNextGeneralSteps = false; _isNextGeneralCycleStep = false; }
	const bool IsComplite() const { return _isComplete; }
	void Next();

private:
	FXLagBuildParameterEvaluator* _evaluator;
	const FGeneralPlain* GeneralPlain = nullptr;
	int32 _generalStepIndex = -1;
	int32 _subStepIndex = -1;
	bool _isComplete = false;

	bool _isNextGeneralSteps = false;
	bool _isNextGeneralCycleStep = false;
	int _generalStepCount = 0;

	void BeginInitialize();
	void InitializeNextGeneralStep();
	void IntializeBeginSubStep();
	void FindNextSubStep();
	void NextSubStep();
	void InitializeComplite();

	const FSubStep* FindSubStepById(const FString& stepId) const;
};