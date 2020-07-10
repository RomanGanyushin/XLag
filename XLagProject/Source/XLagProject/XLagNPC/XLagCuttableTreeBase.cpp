// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagCuttableTreeBase.h"

// Sets default values
AXLagCuttableTreeBase::AXLagCuttableTreeBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

// Called when the game starts or when spawned
void AXLagCuttableTreeBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXLagCuttableTreeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (State == AXLagCuttableTreeState::Falling)
	{
		AddActorLocalOffset(FVector(0, 0, 90.f / (90.0 / 0.25f)));
		AddActorLocalRotation(FRotator(0.25f, 0, 0));

		UE_LOG(LogTemp, Log, TEXT("Tree Pitch %f"), GetActorRotation().Pitch);
	
		if (GetActorRotation().Pitch > 85)
		{
			State = AXLagCuttableTreeState::Fallen;
		}
	}
}

void AXLagCuttableTreeBase::Cut(int force)
{
	if (State == AXLagCuttableTreeState::Growing)
	{
		UE_LOG(LogTemp, Log, TEXT("Tree sustainability: %f"), Sustainability);
		Sustainability -= force;

		if (Sustainability < 0)
		{
			State = AXLagCuttableTreeState::Falling;
			//		AddRelativeRotation(FRotator(1, 0, 0));
			AddActorLocalRotation(FRotator(force * sin(((float)Sustainability) / 1.0), 0, 0));
		}
	}
}

bool AXLagCuttableTreeBase::IsCutted()
{
	return State != AXLagCuttableTreeState::Growing;
}

bool AXLagCuttableTreeBase::CanBroach()
{
	return State == AXLagCuttableTreeState::Fallen;
}

void AXLagCuttableTreeBase::Broach(int force)
{
	if (State == AXLagCuttableTreeState::Timber)
		return;

	State = AXLagCuttableTreeState::Timber;

	if (TimberObject == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("TimberObject is null"));
		return;
	}

	AliveTree->SetStaticMesh(TimberObject);
	AliveTree->SetRelativeScale3D(FVector(TimberDiameter, TimberDiameter, TimberLength));
	SetActorScale3D(FVector(1, 1, 1));
}

bool AXLagCuttableTreeBase::IsTimber()
{
	return State == AXLagCuttableTreeState::Timber;
}

void AXLagCuttableTreeBase::UpdateAge(float age)
{
	Age = age;
	float scale = 0.1f + age / 100;
	this->SetActorScale3D(FVector(scale, scale, scale));
}
