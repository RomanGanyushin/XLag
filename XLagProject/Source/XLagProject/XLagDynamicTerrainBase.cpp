/// Fill out your copyright notice in the Description page of Project Settings.

#include "XLagDynamicTerrainBase.h"
#include "ProceduralMeshComponent.h"
#include "XLagDynamicTerrain\XLagDynamicTerrainMapFiller.hpp"

#include "XLagDynamicTerrain\MapBuilder\TerrainElementEnum.h"
#include "XLagDynamicTerrain\MapBuilder\TerrainMapEditEditor.h"
#include "XLagDynamicTerrain\MapBuilder\Components\PerlinFillerMapEditComponent.h"
#include "XLagDynamicTerrain\MapBuilder\Components\AligmentEditComponent.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTranformComponent.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransofmHigherCondition.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransofmBelowCondition.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransformNeighbourCondition.h"
#include "XLagDynamicTerrain\Position\RandomizeZeroPlacePosition.h"
#include "XLagDynamicTerrain\Filters\ResourcePlacementMapItemFilter.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Character.h"
#include "XLagNPC/XLagNPCBase.h"

#include "XLagNPC/XLagNPCSwapManagement.h"



// Sets default values
AXLagDynamicTerrainBase::AXLagDynamicTerrainBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TerrainScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = TerrainScene;
	InitializeLayers();

	InitMap();
	InitGeometry();
	AddGreader();

	UE_LOG(LogTemp, Warning, TEXT("AXLagDynamicTerrainBase construct 056"));

}

void AXLagDynamicTerrainBase::PostActorCreated()
{
	InitMap();
	InitGeometry();
	AddGreader();
	Super::PostActorCreated();
}

void AXLagDynamicTerrainBase::PostLoad()
{
	InitMap();
	InitGeometry();
	AddGreader();
	Super::PostLoad();
}

// Called when the game starts or when spawned
void AXLagDynamicTerrainBase::BeginPlay()
{
	Super::BeginPlay();

	auto management = AXLagNPCSwapManagement::GetManagment();
	if (management != nullptr)
	{
		management->SetMapAccessor(CurrentMap);

		management->DoSwapTrees();
		UE_LOG(LogTemp, Log, TEXT("Do Swap Trees"));

		management->DoSwapPersons();
		UE_LOG(LogTemp, Log, TEXT("Do Swap Persons"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Swap managment not found"));
	}

	APawn *avatar = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (avatar == nullptr)
		return;

	auto locator = RandomizeZeroPlacePosition(Map).Get();
	avatar->SetActorLocation(locator + FVector(0, 0, 200));


	/*for (TObjectIterator<ACharacter> It; It; ++It)
	{
		ACharacter* CurrentObject = *It;
		UE_LOG(LogTemp, Log, TEXT(">>> Found UObject named: %s"), *CurrentObject->GetName());

		if (CurrentObject->GetName().Equals(TEXT("BuilderCharter_2"), ESearchCase::CaseSensitive))
		{
			CurrentObject->AddMovementInput(FVector(1.f, 0.f, 0.f));
			UE_LOG(LogTemp, Log, TEXT(">>>>>>>>>>>>>>> Moving >>>>>>>>>>>>>>>>>>>"));
		}
	}*/
}

// Called every frame
void AXLagDynamicTerrainBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	return;

	//for (TObjectIterator<ACharacter> It; It; ++It)
	//{
	//	ACharacter* CurrentObject = *It;
	//	UE_LOG(LogTemp, Log, TEXT(">>> Found UObject named: %s"), *CurrentObject->GetName());

	//	if (CurrentObject->GetName().Equals(TEXT("BuilderCharter_2"), ESearchCase::CaseSensitive))
	//	{
	//		FVector toTree = AnyTreeLocation - CurrentObject->GetActorLocation();
	//		toTree.Normalize();

	//		CurrentObject->AddMovementInput(toTree, DeltaTime * 10);
	//		FRotator toTreeRotation = toTree.Rotation();
	//		toTreeRotation.Pitch = 0; // 0 off the pitch 
	//		
	//		auto curRot = CurrentObject->GetActorRotation();
	//		auto delta = toTreeRotation - curRot;
	//		delta.Pitch = 0;
	//		CurrentObject->AddActorLocalRotation(delta);
	//		

	//		UE_LOG(LogTemp, Log, TEXT(">>>>>>>>>>>>>>> Moving >>>>>>>>>>>>>>>>>>>"));
	//		//UE_LOG(LogTemp, Log, TEXT("Rotator %f"), );
	//	}
	//}

	Super::Tick(DeltaTime);
		return;

	APawn *avatar = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (avatar == nullptr)
		return;

	FVector toPlayer = avatar->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), toPlayer.X, toPlayer.Y, toPlayer.Z);
	auto mapCoordsX = (int)toPlayer.X / 100 + 50;
	auto mapCoordsY = (int)toPlayer.Y / 100 + 50;

	auto& level00 = Map->Point(mapCoordsX, mapCoordsY).Stack.back().Level;
	auto& level01 = Map->Point(mapCoordsX, mapCoordsY+1).Stack.back().Level;
	auto& level11 = Map->Point(mapCoordsX+1, mapCoordsY+1).Stack.back().Level;
	auto& level10 = Map->Point(mapCoordsX+1, mapCoordsY).Stack.back().Level;
	
	auto lmin = std::min(std::min(level00, level01), std::min(level11, level10));
	auto lmax = std::max(std::max(level00, level01), std::max(level11, level10));
	auto ldelta = lmax - lmin;
	auto lcut = std::min(ldelta, 1.f);
	
	level00 = std::max(level00 - lcut, lmin) - 1;
	level01 = std::max(level01 - lcut, lmin) - 1;
	level11 = std::max(level11 - lcut, lmin) - 1;
	level10 = std::max(level10 - lcut, lmin) - 1;

	UE_LOG(LogTemp, Warning, TEXT("Level %f"), level00);
	InitGeometry();
	
}

void AXLagDynamicTerrainBase::InitializeLayers()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize layers"));
	
	GroundGrass = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrass"));
	GroundGrass->SetupAttachment(TerrainScene);

	RockSandstone = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RockSandstone"));
	RockSandstone->SetupAttachment(TerrainScene);

	RockBasalt = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RockBasalt"));
	RockBasalt->SetupAttachment(TerrainScene);


	GroundGrassToRockSandstone = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrassToRockSandstone"));
	GroundGrassToRockSandstone->SetupAttachment(TerrainScene);

	GroundGrassToRockBasalt = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrassToRockBasalt"));
	GroundGrassToRockBasalt->SetupAttachment(TerrainScene);
}

void AXLagDynamicTerrainBase::InitMap()
{

	if (Map != nullptr)
	{
		delete Map;
	}

	Map = new XLagDynamicTerrainMap(FullMapSizeX, FullMapSizeY, Scale);
	Map->Initialize();

	CurrentMap = new XLagDynamicTerrainMapWindow(Map, WindowMapSizeX, WindowMapSizeY);

	TerrainMapEditEditor editor(Map);

	// Формирует случайный рельеф.
	PerlinFillerMapEditSettings settings;
	settings.Amplitude = Amplitude;
	settings.Octaves = Octaves;
	PerlinFillerMapEditComponent perlinComp(TerrainElementEnum::GraundGrass, settings);
	editor.FillByXY(&perlinComp);

	// Выравнивание по высоте, так чтобы центральная часть заданным радиусом была в 0 уровне по высоте.
	AligmentEditComponent aligment(AligmentEditComponentSettings(FullMapSizeX / 2, FullMapSizeX / 2, ZeroLocationRadius, ZeroLocationHeight));
	editor.FillByXY(&aligment);

	TerrainElementTranformComponent makeRock(
		TerrainElementTransofmHigherCondition(400),
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::RockBasalt);
	editor.FillByXY(&makeRock);

	TerrainElementTranformComponent makeHollow(
		TerrainElementTransofmBelowCondition(-400),
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::RockSandstone);
	editor.FillByXY(&makeHollow);

	TerrainElementTranformComponent makeTransitionGrassToBasalt
	(
		TerrainElementTransformNeighbourCondition(TerrainElementEnum::RockBasalt),
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::GrondGrassToRockBasaltTrans
	);
	editor.FillByXY(&makeTransitionGrassToBasalt);

	TerrainElementTranformComponent makeTransitionGrassToSandstone
	(
		TerrainElementTransformNeighbourCondition(TerrainElementEnum::RockSandstone),
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::GroundGrassToRockSandstoneTrans
	);
	editor.FillByXY(&makeTransitionGrassToSandstone);

	//// Tree
	auto possiblePlace = Map->GetFilteredItems(ResourcePlacementMapItemFilter(TerrainElementEnum::GraundGrass));
	int placeIndexCount = possiblePlace.size();
	UE_LOG(LogTemp, Log, TEXT("Graund Grass square %d m2"), placeIndexCount);

	if (placeIndexCount == 0 || AreaPerTree <= 0)
		return;

	UE_LOG(LogTemp, Log, TEXT("Area Per Tree %d"), AreaPerTree);

	auto totalTreeCount = std::min(placeIndexCount, placeIndexCount / AreaPerTree);
	if (totalTreeCount == 0)
		return;

	UE_LOG(LogTemp, Log, TEXT("Total Tree Count %d"), totalTreeCount);
	
	if (totalTreeCount > 0)
	{
		std::vector<int> randomizeVector(totalTreeCount);
		std::generate(randomizeVector.begin(), randomizeVector.end(), [placeIndexCount]() mutable {return rand() % placeIndexCount; });

		for(auto index : randomizeVector)
		{
			auto* place = possiblePlace[index];
			place->OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Tree;
		}
	}
}

void AXLagDynamicTerrainBase::InitGeometry()
{

	XLagDynamicTerrainLayerGeometry _geometry;

	_geometry.CreateFrom(Map, TerrainElementEnum::GraundGrass);
	GenerateLayerGeometry(GroundGrass, _geometry);

	_geometry.CreateFrom(Map, TerrainElementEnum::RockSandstone);
	GenerateLayerGeometry(RockSandstone, _geometry);

	_geometry.CreateFrom(Map, TerrainElementEnum::RockBasalt);
	GenerateLayerGeometry(RockBasalt, _geometry);

	_geometry.CreateTransFrom(Map, TerrainElementEnum::GroundGrassToRockSandstoneTrans);
	GenerateLayerGeometry(GroundGrassToRockSandstone, _geometry);

	_geometry.CreateTransFrom(Map, TerrainElementEnum::GrondGrassToRockBasaltTrans);
	GenerateLayerGeometry(GroundGrassToRockBasalt, _geometry);
}

void AXLagDynamicTerrainBase::GenerateLayerGeometry(UProceduralMeshComponent* Component, XLagDynamicTerrainLayerGeometry& geometry)
{
	UE_LOG(LogTemp, Warning, TEXT("GenerateLayerGeometry"));
	Component->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
}

void AXLagDynamicTerrainBase::AddGreader()
{
	return;
	float x = 5000; float y = 5000;
	float z = Map->Point(50, 50).Get()->Level + 10.f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/excavator/greider"));
	
	if (SphereVisualAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("SphereVisualAsset.Succeeded"));

		if (Grader == nullptr)
		{
			Grader = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grader"));
			Grader->SetupAttachment(RootComponent);
			Grader->SetStaticMesh(SphereVisualAsset.Object);
			Grader->SetWorldScale3D(FVector(.1f, .1f, .1f));
			Grader->SetSimulatePhysics(true);
		}

		Grader->SetRelativeLocation(FVector(x, y, z));
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SphereVisualAsset.Fieled"));
	}
}
