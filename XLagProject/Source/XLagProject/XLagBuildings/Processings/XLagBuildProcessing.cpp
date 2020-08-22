#include "XLagBuildProcessing.h"

UXLagBuildProcessing::UXLagBuildProcessing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Evaluator = new FXLagBuildParameterEvaluator();
	GeneralStepIterator = CreateDefaultSubobject<UXLagGeneralStepIterator>("Iterator_GS");
	GeneralStepIterator->SetEvaluator(Evaluator);
}

void UXLagBuildProcessing::DoProcess(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate)
{
	if (meshTemplate == nullptr)
		return;

	if (GeneralStepIterator->IsComplite())
		return;

	if (_repeatCycle != nullptr)
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

void UXLagBuildProcessing::SetGeneralPlain(FGeneralPlain* generalPlain)
{
	Evaluator->SetParameters(generalPlain->Parameters);
	GenerateParametersFrom(generalPlain->Elements);
	GeneralStepIterator->SetGeneralPlain(generalPlain);
}

void UXLagBuildProcessing::GenerateParametersFrom(TArray<FBuildingElement> elements)
{
	for (auto& it : elements)
	{
		Evaluator->SetParameter(FString::Printf(TEXT("%s.Length"), *it.Id), it.Length);
		Evaluator->SetParameter(FString::Printf(TEXT("%s.Width"), *it.Id), it.Width);
		Evaluator->SetParameter(FString::Printf(TEXT("%s.Height"), *it.Id), it.Height);
	}
}

void UXLagBuildProcessing::InitializeSubStep()
{
	auto step = GeneralStepIterator->GetCurrentSubStep();

	if (step == nullptr)
		return;

	SetupPosition(step);
	
	if (_repeatCycle != nullptr)
		delete _repeatCycle;

	_repeatCycle = new FRepeatCycle();
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
		delete _repeatCycle;
		_repeatCycle = nullptr;

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