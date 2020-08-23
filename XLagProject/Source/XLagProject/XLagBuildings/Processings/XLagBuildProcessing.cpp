#include "XLagBuildProcessing.h"

#include "ProceduralMeshComponent.h"
#include "XLagDynamicBuildingElementGeometry.h"

UXLagBuildProcessing::UXLagBuildProcessing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Evaluator = new FXLagBuildParameterEvaluator();
	GeneralStepIterator = new FXLagGeneralStepIterator();
	GeneralStepIterator->SetEvaluator(Evaluator);
}

void UXLagBuildProcessing::DoProcess(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate, UMaterial* woodMaterial)
{
	if (meshTemplate == nullptr)
		return;

	if (GeneralStepIterator->IsComplite())
		return;

	if (_repeatCycle != nullptr)
	{
		ExecuteRepeatCycle(owner, root, meshTemplate, woodMaterial);
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
		SetupPosition(&generalStep->Repeat);
		GeneralStepIterator->Confirm();
	}

	InitializeSubStep();
}

void UXLagBuildProcessing::SetGeneralPlain(FGeneralPlain* generalPlain)
{
	GeneralPlain = generalPlain;
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

void UXLagBuildProcessing::ExecuteRepeatCycle(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate, UMaterial* woodMaterial)
{
	SpawnBuildingElement(owner, root, meshTemplate, woodMaterial);


	_repeatCycle->Index++;

	if (_repeatCycle->Count <= _repeatCycle->Index)
	{
		delete _repeatCycle;
		_repeatCycle = nullptr;

		GeneralStepIterator->Next();
	}
}

void UXLagBuildProcessing::SpawnBuildingElement(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate, UMaterial* woodMaterial)
{
	auto step = GeneralStepIterator->GetCurrentSubStep();
	auto elementId = step->ElementId;
	auto element = GeneralPlain->Elements.FindByPredicate([elementId](auto& it) { return it.Id.Equals(elementId, ESearchCase::IgnoreCase);});

	int argIndex = 1;
	for (auto& it: step->ElementParams)
	{
		auto value = Evaluator->Evaluate(it);
		Evaluator->SetParameter(FString::Printf(TEXT("%s.Arg%d"),*element->Id, argIndex++), FString::Printf(TEXT("%f"), value));
	}

	if (element == nullptr)
	{
		// Log Error;
		return;
	}

	if (element->Type.Equals(TEXT("Internal"), ESearchCase::IgnoreCase))
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
	else if(element->Type.Equals(TEXT("Custom"), ESearchCase::IgnoreCase))
	{
		auto custom = NewObject<UProceduralMeshComponent>(owner);
		custom->SetupAttachment(root);

		XLagDynamicBuildingElementGeometry geometry;
		geometry.Create(element->Geometry, Evaluator);

		custom->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
		custom->SetRelativeRotation(Evaluator->CurrentOrientation);
		custom->SetRelativeLocation(Evaluator->CurrentPosition);
		custom->SetMaterial(0, woodMaterial);
		custom->RegisterComponent();

		Evaluator->OffsetPosition(_repeatCycle->IncrementalPosition);
		Evaluator->OffsetOrientation(_repeatCycle->IncrementalRotator);
	}

	
}