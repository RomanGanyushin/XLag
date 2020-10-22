#include "XLagCrop.h"
#include "../Common/CellOperationProcessing.h"

AXLagCrop::AXLagCrop()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AXLagCrop::Initialize(XLagDynamicTerrainMapItem* cell, FXLagCropDescription description)
{
	Description = description;
	Cell = cell;
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

	CellOperationProcessing operation(Cell, CellOperationEnum::Evolution);
	LocalTime = operation.Get() / 100.0;
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
		auto currentStageTime = GetLocalStageTime();

		if (currentStage->StageLifeTime > currentStageTime)
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
	auto localStageTime = GetLocalStageTime();
	auto scaleOfTime = stage->StartScale + (1.0 - (stage->StageLifeTime - localStageTime) / (stage->StageLifeTime)) * (stage->FinalScale - stage->StartScale);
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

float AXLagCrop::GetLocalStageTime() const
{
	auto result = LocalTime;
	for (auto& it : Description.CropStages)
	{
		if (it.StageLifeTime <= result)
		{
			result -= it.StageLifeTime;
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