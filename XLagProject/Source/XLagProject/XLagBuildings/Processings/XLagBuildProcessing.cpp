#include "XLagBuildProcessing.h"

UXLagBuildProcessing::UXLagBuildProcessing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Evaluator = CreateDefaultSubobject<UXLagBuildParameterEvaluator>("Evaluator");
	GeneralStepIterator = CreateDefaultSubobject<UXLagGeneralStepIterator>("Iterator_GS");
}

void UXLagBuildProcessing::DoProcess(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate)
{
	if (meshTemplate == nullptr)
		return;

	if (GeneralStepIterator->IsComplite())
		return;

	if (_repeatCycle.Get() != nullptr)
	{
		ExecuteRepeatCycle(owner, root, meshTemplate);
		return;
	}

	if (GeneralStepIterator->IsNewGeneralStep())
	{
		// Initialize general step;
		auto generalStep = GeneralStepIterator->GetCurrentGeneralStep();
		SetupPosition(generalStep);

		GeneralStepIterator->Confirm();
	}

	if (GeneralStepIterator->IsNextGeneralCycleStep())
	{
		auto generalStep = GeneralStepIterator->GetCurrentGeneralStep();
		auto incrementalPosition = Evaluator->Evaluate(generalStep->Repeat.OffsetLocal);
		auto incrementalRotator = Evaluator->Evaluate(generalStep->Repeat.OffsetOrientation);
		Evaluator->OffsetPosition(incrementalPosition);
		Evaluator->OffsetOrientation(incrementalRotator);

		GeneralStepIterator->Confirm();
	}

	InitializeSubStep();
}

void UXLagBuildProcessing::SetGeneralPlain(TSharedPtr<FGeneralPlain> generalPlain)
{
	GeneralStepIterator->SetGeneralPlain(generalPlain.Get());
}

void UXLagBuildProcessing::InitializeSubStep()
{
	auto step = GeneralStepIterator->GetCurrentSubStep();

	if (step == nullptr)
		return;

	SetupPosition(step);
	
	_repeatCycle = MakeShareable(new FRepeatCycle());
	_repeatCycle->Count = Evaluator->EvaluateInt(step->Repeat.Count);
	_repeatCycle->IncrementalPosition = Evaluator->Evaluate(step->Repeat.OffsetLocal);
	_repeatCycle->IncrementalRotator = Evaluator->Evaluate(step->Repeat.OffsetOrientation);
}

void UXLagBuildProcessing::SetupPosition(const FPositionSetup* setup)
{
	if (!setup->Local.IsEmpty())
	{
		auto ref = Evaluator->Evaluate(setup->Local);
		Evaluator->ResetLocal(ref);
	}

	if (!setup->Orientation.IsEmpty())
	{
		auto ori = Evaluator->Evaluate(setup->Orientation);
		Evaluator->ResetOrientation(ori);
	}

	if (!setup->OffsetLocal.IsEmpty())
	{
		auto offset = Evaluator->Evaluate(setup->OffsetLocal);
		Evaluator->OffsetPosition(offset);
	}

	if (!setup->OffsetOrientation.IsEmpty())
	{
		auto offset = Evaluator->Evaluate(setup->OffsetOrientation);
		Evaluator->OffsetOrientation(offset);
	}
}

void UXLagBuildProcessing::ExecuteRepeatCycle(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate)
{
	SpawnBuildingElement(owner, root, meshTemplate);
	_repeatCycle->Index++;

	if (_repeatCycle->Count <= _repeatCycle->Index)
	{
		_repeatCycle.Reset();
		GeneralStepIterator->Next();
	}
}

void UXLagBuildProcessing::SpawnBuildingElement(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate)
{
	auto brick = NewObject<UStaticMeshComponent>(owner);
	brick->SetupAttachment(root);
	brick->SetStaticMesh(meshTemplate);
	brick->SetRelativeRotation(Evaluator->CurrentOrientation);
	brick->SetRelativeLocation(Evaluator->CurrentPosition);
	brick->SetRelativeScale3D(FVector(0.2, 0.1, 0.05));
	brick->RegisterComponent();

	Evaluator->OffsetPosition(_repeatCycle->IncrementalPosition);
	Evaluator->OffsetOrientation(_repeatCycle->IncrementalRotator);
}