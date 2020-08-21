#pragma once
#include "../Models/GeneralPlain.h"
#include "XLagGeneralStepIterator.generated.h"

UCLASS()
class UXLagGeneralStepIterator : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void SetGeneralPlain(FGeneralPlain *generalPlain);
	const FGeneralStep* GetCurrentGeneralStep() const;
	const FSubStep* GetCurrentSubStep() const;
	const bool IsNewGeneralStep() const { return _isNextGeneralSteps; }
	const bool IsNextGeneralCycleStep() const { return _isNextGeneralCycleStep; }
	void Confirm() { _isNextGeneralSteps = false; _isNextGeneralCycleStep = false; }
	const bool IsComplite() const { return _isComplete; }
	void Next();

private:
	FGeneralPlain* GeneralPlain = nullptr;
	int32 _generalStepIndex = -1;
	int32 _subStepIndex = -1;
	bool _isComplete = false;

	bool _isNextGeneralSteps = false;
	bool _isNextGeneralCycleStep = false;
	int _generalStepCount = 0;

	void BeginInitialize();
	void InitializeBeginGeneralStep();
	void InitializeNextGeneralStep();
	void IntializeBeginSubStep();
	void FindNextSubStep();
	void NextSubStep();
	void InitializeComplite();

	const FSubStep* FindSubStepById(const FString& stepId) const;
};