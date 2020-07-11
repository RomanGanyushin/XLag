// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagTimberStack.h"

// Sets default values
AXLagTimberStack::AXLagTimberStack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
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

void AXLagTimberStack::AddTimber(AXLagCuttableTreeBase* tree)
{
	tree->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));	

	auto diameter = tree->TimberDiameter * 100;
	auto position = CalculatePosition(Count + 1, diameter) + FVector(0, 0, diameter / 2.f);
	tree->SetActorRelativeLocation(position);
	tree->SetActorRelativeRotation(FRotator(0, 0, 90));
	tree->SetActorEnableCollision(true);
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
				result = l == 0 ? FVector((ml + 1) / 2 * diameter, 0, 0) : FVector(-diameter/2.0, 0, DeltaHeigth(diameter));
				if (++l > ml){ ml++; dir = 2; l = 0;}
			}
			break;
			
			case 2:
			{
				result = l == 0 ? FVector(-1.f * diameter * (ml) / 2, 0, 0) : FVector(diameter / 2.0, 0, DeltaHeigth(diameter));
				if (++l > ml) { ml++; dir = 1; l = 0;}
			}
			break;
		}

	} while (++index < num);

	return result;
}