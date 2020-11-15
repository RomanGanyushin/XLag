#include "XLagCrop.h"
//#include "../Common/CellOperationProcessing.h"
#include "../XLagDynamicObject/ObjectModels/TerrainCropObject.h"

AXLagCrop::AXLagCrop()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AXLagCrop::Initialize(FXLagDynamicObject* object, FXLagCropDescription description)
{
	Description = description;
	_object = object;
}

bool AXLagCrop::IsVaild() const
{
	return Description.CropStages.Num() > 0;
}

void AXLagCrop::BeginPlay()
{
	Super::BeginPlay();
}

void AXLagCrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TerrainCropObject cropObject(*_object);
	Progression = cropObject.GetEvalution();
	UpdateView();
}

void AXLagCrop::UpdateView()
{
	if (!IsVaild())
		return;

	if (CurrentMeshComponent == nullptr)
	{
		CreateStageView();
	}
	else
	{
		auto currentStage = GetCurrentStage();
		auto currentStageProgression = GetLocalStageProgression();

		if (currentStage->PartOfTimeLife > currentStageProgression)
		{
			UpdateStageView();
		}
		else
		{
			if (CurrentStage < Description.CropStages.Num() - 1)
			{
				NextStage();
			}
		}
	}
}

void AXLagCrop::UpdateStageView()
{
	auto stage = GetCurrentStage();
	auto localStageProgression = GetLocalStageProgression();
	auto scaleOfTime = stage->StartScale + (localStageProgression / 100.0) * (stage->FinalScale - stage->StartScale);
	CurrentMeshComponent->SetRelativeScale3D(scaleOfTime * FVector(1.f, 1.f, 1.f));
}

void AXLagCrop::NextStage()
{
	DestroyStageView();
	CurrentStage++;
	CreateStageView();
}

void AXLagCrop::CreateStageView()
{
	auto stage = GetCurrentStage();
	CurrentMeshComponent = NewObject<UStaticMeshComponent>(RootComponent);
	CurrentMeshComponent->SetupAttachment(RootComponent);
	CurrentMeshComponent->SetStaticMesh(stage->CropTemplate);
	CurrentMeshComponent->SetRelativeScale3D(stage->StartScale * FVector(1.f, 1.f, 1.f));
	CurrentMeshComponent->RegisterComponent();
}

void AXLagCrop::DestroyStageView()
{
	CurrentMeshComponent->UnregisterComponent();
	delete CurrentMeshComponent;
	CurrentMeshComponent = nullptr;
}

float AXLagCrop::GetLocalStageProgression() const
{
	auto result = Progression;
	for (auto& it : Description.CropStages)
	{
		if (it.PartOfTimeLife < result)
		{
			result -= it.PartOfTimeLife;
		}
		else
		{
			break;
		}
	}
	return result;
}

const FXLagCropStage* AXLagCrop::GetCurrentStage() const
{
	if (CurrentStage < 0 || CurrentStage >= Description.CropStages.Num())
		return nullptr;

	return &Description.CropStages[CurrentStage];
}