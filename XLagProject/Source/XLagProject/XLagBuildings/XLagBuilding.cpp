// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagBuilding.h"
#include "XLagBuildingElement.h"

//#include "Hal/PlatformFilemanager.h"
//#include "JsonObjectConverter.h"
//#include "Models/GeneralPlain.h"

#include "Models/GeneralPlainSerialization.h"

// Sets default values
AXLagBuilding::AXLagBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> asset(TEXT("/Game/Buildings/Brick"));
	UE_LOG(LogTemp, Log, TEXT("AXLagBuilding::Begin Play"));

	if (asset.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("AXLagBuilding::Succeeded"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AXLagBuilding::Fail"));
	}

	int brick_identify = 0; float k = 2;

	asset.StaticInit();

	for (int j = 0; j < 20; j++)
		for (int i = 0; i < 10; i++)
		{
			auto name = FName(FString::Printf(TEXT("Brick_%d"), brick_identify++));
			auto brick = CreateDefaultSubobject<UStaticMeshComponent>(name, asset.Object);
			brick->SetupAttachment(RootComponent);
			brick->SetStaticMesh(asset.Object);
			brick->SetWorldLocation(FVector(5000 + 20 * k* i + 10 * k * (j % 2), 5500, +5 * j *k));
			brick->SetWorldScale3D(FVector(0.2 *k, 0.1*k, 0.05*k));
		}

	UGeneralPlainSerialization::LoadFromFile(FString(TEXT("building.json")));
}

// Called when the game starts or when spawned
void AXLagBuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXLagBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

