// Fill out your copyright notice in the Description page of Project Settings.
#include "XLagCuttableTreeBase.h"
#include "../XLagDynamicObject/ObjectModels/TerrainTreeObject.h"

// Sets default values
AXLagCuttableTreeBase::AXLagCuttableTreeBase()
{
}

void AXLagCuttableTreeBase::Initialize()
{
	auto asset = this->GetAsset();
	if (asset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("asset is null"));
		return;
	}

	if (asset->Succeeded())
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
		AliveTree = CreateDefaultSubobject<UStaticMeshComponent>("Mesh tree");
		AliveTree->SetupAttachment(RootComponent);
		AliveTree->SetStaticMesh(asset->Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("asset is fail"));
	}

	auto timberAsset = GetTimberAsset();
	if (!timberAsset->Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("Timber Asset is was not success loaded"));
		return;
	}

	TimberObject = timberAsset->Object;

	if (TimberObject == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Timber object is null"));
		return;
	}
}

void AXLagCuttableTreeBase::SetObject(FXLagDynamicObject* object)
{
	object->PropertyChangedEvent.AddDynamic(this, &AXLagCuttableTreeBase::OnPropertyChanged);
}

void AXLagCuttableTreeBase::OnPropertyChanged(uint8 id, const FXLagObjectProperties& properties)
{
	TerrainTreeObject treeProperties(*(const_cast<FXLagObjectProperties*>(&properties)));
	
	if (id == TreeParameterId::ParId_TreeState)
	{	
		auto treeState = treeProperties.GetTreeState();

		if (treeState == TreeState::Timber_)
		{
			AliveTree->SetStaticMesh(TimberObject);
			AliveTree->SetRelativeScale3D(FVector(TimberDiameter, TimberDiameter, TimberLength));
			SetActorScale3D(FVector(1, 1, 1));
		}
	}

	if (id == CommonParameterId::ParId_Location)
	{
		SetActorLocation(treeProperties.GetLocation());
	}

	if (id == CommonParameterId::ParId_Rotation)
	{
		SetActorRotation(treeProperties.GetRotation());
	}
}

// Called when the game starts or when spawned
void AXLagCuttableTreeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AXLagCuttableTreeBase::UpdateAge(float age)
{
	Age = age;
	float scale = 0.1f + age / 100;
	this->SetActorScale3D(FVector(scale, scale, scale));
}
