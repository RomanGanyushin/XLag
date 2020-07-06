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
		auto newObject = CreateDefaultSubobject<UStaticMeshComponent>("Mesh tree");
		newObject->SetupAttachment(RootComponent);
		newObject->SetStaticMesh(asset->Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("asset is fail"));
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

	if (State == 1)
	{
		this->AddActorLocalOffset(FVector(0, 0, 70));
		State = 2;
	}

	if (State == 2)
	{

		AddActorLocalRotation(FRotator(0.25, 0, 0));
		auto rot = GetActorRotation();
		if (rot.Pitch > 85)
		{
			State = 3;
		}

		UE_LOG(LogTemp, Log, TEXT(">>>>>>>>>>>>>>> Pitch %f"), rot.Pitch);
	}
}

void AXLagCuttableTreeBase::Cut(int force)
{
	if (State == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Tree sustainability: %f"), Sustainability);
		Sustainability -= force;

		if (Sustainability < 0)
		{
			State = 1;
			//		AddRelativeRotation(FRotator(1, 0, 0));
			AddActorLocalRotation(FRotator(force * sin(((float)Sustainability) / 10.0), 0, 0));
		}
	}
}

bool AXLagCuttableTreeBase::CanTake()
{
	return State == 3;
}

bool AXLagCuttableTreeBase::CanCut()
{
	return State == 0;
}

void AXLagCuttableTreeBase::UpdateAge(float age)
{
	Age = age;
	float scale = 0.1f + age / 100;
	this->SetActorScale3D(FVector(scale, scale, scale));
}