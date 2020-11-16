#include "XLagCrop.h"
#include "../XLagDynamicObject/ObjectModels/TerrainCropObject.h"

AXLagCrop::AXLagCrop()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AXLagCrop::Initialize(FXLagCropDescription description)
{
	Description = description;
}

void AXLagCrop::AssignObject(const FXLagDynamicObject& object)
{
	AXLagSwapableObject::AssignObject(object);
	const_cast<FXLagDynamicObject*>(&object)->PropertyChangedEvent.AddDynamic(this, &AXLagCrop::OnPropertyChanged);
}


bool AXLagCrop::IsVaild() const
{
	return Description.CropStages.Num() > 0;
}

void AXLagCrop::OnPropertyChanged(uint8 id, const FXLagObjectProperties& properties)
{
	TerrainCropObject cropProperties(*(const_cast<FXLagObjectProperties*>(&properties)));

	if (id == CropParameterId::ParId_CropEvalution)
	{
		Progression = cropProperties.GetEvalution();
		UpdateView();
	}
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