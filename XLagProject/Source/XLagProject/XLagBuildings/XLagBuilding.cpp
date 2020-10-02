// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagBuilding.h"
#include "Models/GeneralPlainSerialization.h"

// Sets default values
AXLagBuilding::AXLagBuilding()
	:_plain(nullptr)
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
}

// Called every frame
void AXLagBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLagBuilding::Build()
{
	if (_processing == nullptr)
	{
		_processing = NewObject<UXLagBuildProcessing>();
		_processing->SetGeneralPlain(_plain);	
	}

	_processing->DoProcess(this, RootComponent);
}

void AXLagBuilding::SetGeneralPlain(const FGeneralPlain* plain)
{
	_plain = plain;
}

void AXLagBuilding::DoShowPreview(bool isShow)
{	
	if (_plain == nullptr)
		return;

	if (_processing != nullptr)
		return;

	_processing = NewObject<UXLagBuildProcessing>();
	_processing->SetGeneralPlain(_plain);
	_processing->CreatePreview(this, RootComponent);

	this->SetActorEnableCollision(false);
}

