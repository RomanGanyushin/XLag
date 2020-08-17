// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagBuilding.h"
#include "XLagBuildingElement.h"

// Sets default values
AXLagBuilding::AXLagBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> asset(TEXT("/Game/Buildings/Brick"));
	if (asset.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("AXLagBuilding::Succeeded"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AXLagBuilding::Fail"));
	}

	auto brick = CreateDefaultSubobject<UStaticMeshComponent>("Brick", asset.Object);
	brick->SetupAttachment(RootComponent);
	brick->SetStaticMesh(asset.Object);
	brick->SetWorldLocation(FVector(5000, 5000, 100));
	brick->SetWorldScale3D(FVector(0.2, 0.1, 0.05));
}

// Called when the game starts or when spawned
void AXLagBuilding::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("AXLagBuilding::Begin Play"));
}

// Called every frame
void AXLagBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

