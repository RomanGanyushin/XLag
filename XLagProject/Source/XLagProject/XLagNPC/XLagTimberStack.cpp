// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagTimberStack.h"

// Sets default values
AXLagTimberStack::AXLagTimberStack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Tepmplate = GetTimberAsset()->Object;
}

// Called when the game starts or when spawned
void AXLagTimberStack::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXLagTimberStack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLagTimberStack::AddTimber()
{
	float TimberDiameter = 0.4;
	float TimberLength = 4;

	auto log = NewObject<UStaticMeshComponent>(this);
	log->SetupAttachment(RootComponent);
	log->SetStaticMesh(Tepmplate);
	auto diameter = TimberDiameter * 100;
	auto position = CalculatePosition(Count + 1, diameter) + FVector(0, 0, diameter / 2.f);
	log->SetRelativeLocation(position);
	log->SetRelativeRotation(FRotator(0, 0, 90));
	log->SetRelativeScale3D(FVector(TimberDiameter, TimberDiameter, TimberLength));
	log->RegisterComponent();
	//log->SetEnableCollision(true);
	Count++;
}


FVector AXLagTimberStack::CalculatePosition(int num, float diameter)
{
	if (num <= 0)
		return FVector::ZeroVector;

	int index = 0; int dir = 0; int l=0; int ml=1; 
	FVector result = FVector::ZeroVector;

	do 
	{
		switch (dir)
		{
			case 0:
				dir = 1;
			break;

			case 1:
			{
				if (l == 0) result = FVector((ml + 1) / 2 * diameter, 0, 0); 
				else result += FVector(-diameter / 2.0, 0, DeltaHeigth(diameter));

				if (++l > ml){ ml++; dir = 2; l = 0;}
			}
			break;
			
			case 2:
			{
				if (l == 0) result = FVector(-1.f * diameter * (ml) / 2, 0, 0);
				else result += FVector(diameter / 2.0, 0, DeltaHeigth(diameter));

				if (++l > ml) { ml++; dir = 1; l = 0;}
			}
			break;
		}
	} while (++index < num);

	return result;
}