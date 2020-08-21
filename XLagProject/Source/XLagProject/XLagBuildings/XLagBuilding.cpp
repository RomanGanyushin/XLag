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
}

// Called when the game starts or when spawned
void AXLagBuilding::BeginPlay()
{
	Super::BeginPlay();

	
	UE_LOG(LogTemp, Log, TEXT("AXLagBuilding::Begin Play"));

	_plain = UGeneralPlainSerialization::LoadFromFile(FString(TEXT("building.json")));

	_processing = NewObject<UXLagBuildProcessing>();
	_processing->SetGeneralPlain(_plain);	
}

// Called every frame
void AXLagBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_processing == nullptr)
		return;

	_processing->DoProcess(this, RootComponent, BrickTemplet);
}

