#include "XLagBuildProcessing.h"

UXLagBuildProcessing::UXLagBuildProcessing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Evaluator = CreateDefaultSubobject<UXLagBuildParameterEvaluator>("Evaluator");
}

void UXLagBuildProcessing::DoProcess(UObject* owner, USceneComponent*root, UStaticMesh *meshTemplate)
{
	if (meshTemplate == nullptr)
		return;

	if (CurrentGeneralStep == nullptr)
		return;

	static int brick_identify = 0; float k = 2;

	for (size_t i = 0; i < CurrentGeneralStep->SubStepIds.Num(); i++)
	{
		auto& subStepId = CurrentGeneralStep->SubStepIds[i];
		auto step = FindSubStepById(subStepId);
		if (step == nullptr)
			continue;
		
		auto ref = Evaluator->Evaluate(step->Local) * 100 * k;
		auto ori = Evaluator->Evaluate(step->Orientation);
	
		auto repeat = Evaluator->EvaluateInt(step->Repeat.Count);
		
		auto incPos = Evaluator->Evaluate(step->Repeat.IncrementalPosition) * 100 * k;
		auto incRot = Evaluator->Evaluate(step->Repeat.IncrementalRotation);
		
		for (size_t j = 0; j < repeat; j++)
		{
			auto name = FName(FString::Printf(TEXT("Brick_%d"), brick_identify++));
			auto brick = NewObject<UStaticMeshComponent>(owner, name);
			brick->SetupAttachment(root);
			brick->SetStaticMesh(meshTemplate);
			brick->SetRelativeRotation(ori);
			brick->SetRelativeLocation(ref);	
			brick->SetRelativeScale3D(FVector(0.2 *k, 0.1*k, 0.05*k));
			brick->RegisterComponent();

			ref += incPos;
		}
	}
}

void UXLagBuildProcessing::SetGeneralPlain(TSharedPtr<FGeneralPlain> generalPlain)
{
	GeneralPlain = generalPlain;
	InitializePlain();
}

void UXLagBuildProcessing::InitializePlain()
{
	BuildingName = GeneralPlain->BuildingName;
	if (GeneralPlain->GeneralSteps.Num() == 0)
	{
		// To Complite
		return;
	}

	CurrentGeneralStep = &GeneralPlain->GeneralSteps[0];
}

const FSubStep* UXLagBuildProcessing::FindSubStepById(const FString& stepId) const
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