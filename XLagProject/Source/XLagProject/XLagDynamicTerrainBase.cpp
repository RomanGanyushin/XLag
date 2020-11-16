/// Fill out your copyright notice in the Description page of Project Settings.

#include "XLagDynamicTerrainBase.h"
#include <random>
#include <ctime>
#include "ProceduralMeshComponent.h"
#include "XLagDynamicTerrain\XLagDynamicTerrainMapFiller.hpp"

#include "Common\TerrainElementEnum.h"
#include "Common\CellOperationProcessing.h"

#include "XLagDynamicTerrain\XLagDynamicTerrainMapInitializer.h"
#include "XLagDynamicTerrain\XLagDynamicTerrainMapAccessor.h"
#include "XLagDynamicTerrain\MapBuilder\TerrainMapEditEditor.h"
#include "XLagDynamicTerrain\MapBuilder\Components\PerlinFillerMapEditComponent.h"
#include "XLagDynamicTerrain\MapBuilder\Components\AligmentEditComponent.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTranformComponent.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransofmHigherCondition.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransofmBelowCondition.h"
#include "XLagDynamicTerrain\MapBuilder\Components\TerrainElementTransformNeighbourCondition.h"
#include "XLagDynamicTerrain\Position\RandomizeZeroPlacePosition.h"
#include "XLagDynamicTerrain\Filters\ResourcePlacementMapItemFilter.h"
#include "XLagGeometry\Builders\XLagColorizeMapGeometryBuilder.h"
#include "XLagGeometry\Builders\XLagDynamicTerrainLayerGeometry.h"
#include "XLagBuildings\XLagBuildingManager.h"

#include "XLagDynamicObject/ObjectModels/TerrainTreeObject.h"

#include "Kismet/GameplayStatics.h"
#include "XLagProjectGameMode.h"
#include "XLagNPC/XLagNPCSwapManagement.h"



// Sets default values
AXLagDynamicTerrainBase::AXLagDynamicTerrainBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TerrainScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = TerrainScene;
	InitializeLayers();

	//InitMap();
	//InitGeometry();
	//AddGreader();

	UE_LOG(LogTemp, Warning, TEXT("AXLagDynamicTerrainBase construct 056"));

}

void AXLagDynamicTerrainBase::PostActorCreated()
{
	Super::PostActorCreated();

	//InitMap();
	//InitGeometry();
	//AddGreader();
}

void AXLagDynamicTerrainBase::PostLoad()
{
	Super::PostLoad();

	/*InitMap();
	InitGeometry();*/
	
	//AddGreader();
}

void AXLagDynamicTerrainBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called when the game starts or when spawned
void AXLagDynamicTerrainBase::OnInitialze(AGameModeBase* gameMode)
{
	Initialized = true;

	InitMap(gameMode);
	InitGeometry();

	auto swapManager = AXLagNPCSwapManagement::GetManagment();
	auto buildingManager = AXLagBuildingManager::GetManagment();

	if (swapManager != nullptr)
	{
		swapManager->SetMapAccessor(Map);

		//swapManager->DoSwapTrees();
		//UE_LOG(LogTemp, Log, TEXT("Do Swap Trees"));

		swapManager->DoSwapTreeStack();
		UE_LOG(LogTemp, Log, TEXT("Do Swap Tree Stack"));

		swapManager->DoSwapPersons();
		UE_LOG(LogTemp, Log, TEXT("Do Swap Persons"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Swap managment not found"));
	}

	if (buildingManager != nullptr)
	{
		buildingManager->SetMapAccessor(CurrentMap);
	}

	//APawn *avatar = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//if (avatar == nullptr)
	//	return;

	//auto locator = RandomizeZeroPlacePosition(Map).Get();
	//avatar->SetActorLocation(locator + FVector(0, 0, 200));
}
// Called every frame
void AXLagDynamicTerrainBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Initialized)
		return;

	float static UpdateDelayConter = 0;

	UpdateDelayConter += DeltaTime;
	if (UpdateDelayConter < 5.0f)
		return;

	if (Map->IsChanged())
	{
		UpdateDelayConter = 0;
		InitGeometry();
	}

	//APawn *avatar = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//if (avatar == nullptr)
	//	return;

}

void AXLagDynamicTerrainBase::ActivateColorizedMap(bool activate)
{
	if (activate == IsActivatedColorizedMap)
		return;

	IsActivatedColorizedMap = activate;
	InitGeometryForColorizeMap();
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

	Coal = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Coal"));
	Coal->SetupAttachment(TerrainScene);

	Cultivated = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Cultivated"));
	Cultivated->SetupAttachment(TerrainScene);

	GroundGrassToRockSandstone = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrassToRockSandstone"));
	GroundGrassToRockSandstone->SetupAttachment(TerrainScene);

	GroundGrassToRockBasalt = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrassToRockBasalt"));
	GroundGrassToRockBasalt->SetupAttachment(TerrainScene);

	GroundGrassToCoal = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrassToCoal"));
	GroundGrassToCoal->SetupAttachment(TerrainScene);

	GroundGrassToCultivated = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GroundGrassToCultivated"));
	GroundGrassToCultivated->SetupAttachment(TerrainScene);

	RockSandstoneToRockBasalt = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RockSandstoneToRockBasalt"));
	RockSandstoneToRockBasalt->SetupAttachment(TerrainScene);


	ColorizeMapper = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ColorizeMapper"));
	ColorizeMapper->SetupAttachment(TerrainScene);
	ColorizeMapper->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AXLagDynamicTerrainBase::InitMap(AGameModeBase* gameMode)
{
	auto& terrainMap = ((AXLagProjectGameMode*)gameMode)->TerrainMap;
	auto& terrainObjects = ((AXLagProjectGameMode*)gameMode)->TerrainObjects;

	XLagDynamicTerrainMapInitializer initializer(terrainMap);

	initializer.BindCreateMineralLayerEventHandler(std::bind(
		&AXLagDynamicTerrainBase::CreateMineralLayerEventHandler,
		this,
		std::placeholders::_1,
		std::placeholders::_2));

	initializer.DoInitialize();

	Map = std::shared_ptr<ITerrainMapAccessor>(new XLagDynamicTerrainMapAccessor(terrainMap));
	CurrentMap = Map->CreateWindow(0,0, WindowMapSizeX, WindowMapSizeY);

	if (terrainMap.IsCreated)
	{
		terrainObjects.RaiseAddNewObjectsEvent();
		return;
	}

	TerrainMapEditEditor editor(Map);

	// Формирует случайный рельеф.
	PerlinFillerMapEditSettings settings;
	settings.Amplitude = Amplitude;
	settings.Octaves = Octaves;
	PerlinFillerMapEditComponent perlinComp(TerrainElementEnum::GraundGrass, settings);
	editor.FillByXY(&perlinComp);

	// Выравнивание по высоте, так чтобы центральная часть заданным радиусом была в 0 уровне по высоте.
	AligmentEditComponentSettings aligmentSettings(FullMapSizeX / 2, FullMapSizeX / 2, ZeroLocationRadius, ZeroLocationHeight);
	AligmentEditComponent aligment(aligmentSettings);
	editor.FillByXY(&aligment);

	TerrainElementTransofmHigherCondition thc(400);
	TerrainElementTranformComponent makeRock(
		thc,
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::RockBasalt);
	editor.FillByXY(&makeRock);

	TerrainElementTransofmBelowCondition tbc(-400);
	TerrainElementTranformComponent makeHollow(
		tbc,
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::RockSandstone);
	editor.FillByXY(&makeHollow);

	TerrainElementTransformNeighbourCondition tnc_gb(TerrainElementEnum::RockBasalt);
	TerrainElementTranformComponent makeTransitionGrassToBasalt
	(
		tnc_gb,
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::GrondGrassToRockBasaltTrans
	);
	editor.FillByXY(&makeTransitionGrassToBasalt);

	TerrainElementTransformNeighbourCondition tnc_rb(TerrainElementEnum::RockSandstone);
	TerrainElementTranformComponent makeTransitionGrassToSandstone
	(
		tnc_rb,
		TerrainElementEnum::GraundGrass,
		TerrainElementEnum::GroundGrassToRockSandstoneTrans
	);
	editor.FillByXY(&makeTransitionGrassToSandstone);

	//// Формируем элементы ландшафта как ресурсы.

	auto mineralManager = AXLagMineralManager::GetMineralManager();
	if (mineralManager != nullptr && !mineralManager->Empty())
	{
		auto terrainMineralCollection = mineralManager->GetTerrainMineralDescCollection();
		for (auto terrainMineral : terrainMineralCollection)
		{
			ResourcePlacementMapItemFilter filter(terrainMineral.MineralTerrainElement);
			auto region = Map->GetFilteredItems(filter);
			for (auto& cell : region)
			{
				auto topLayer = XLagDynamicTerrainMapItemOperation(*cell).GetForLayerKind(terrainMineral.MineralTerrainElement);
				if (topLayer == nullptr)
					continue;

				topLayer->MineralId = terrainMineral.ID;
			}
		}
	}
		
	//// Tree	
	ResourcePlacementMapItemFilter rp_filter(TerrainElementEnum::GraundGrass);
	auto possiblePlace = Map->GetFilteredItems(rp_filter);
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
		std::mt19937 engine;
		engine.seed(std::time(nullptr));

		std::generate(randomizeVector.begin(), randomizeVector.end(), [engine, placeIndexCount]() mutable {return engine() % placeIndexCount; });

		for(auto index : randomizeVector)
		{
			auto* place = possiblePlace[index];			
			auto loction = Map->GetWorldPosition(place, GetPositionEnum::CenterLowPosition);
			auto rotator = FRotator(0, rand() % 360, 0);

			FXLagObjectProperties properties;
			TerrainTreeObject tree(properties);
			tree.SetLocation(loction);
			tree.SetRotation(rotator);
			tree.SetKind(rand());
			tree.SetAge(20 + rand() % 80);
			tree.SetTreeState(TreeState::Growing);
			tree.SetTreeSustainability(5);

			terrainObjects.AddObject(XLagDynamicObjectType::Tree, place->Index, properties);
		}
	}

	terrainMap.IsCreated = true;
}

void AXLagDynamicTerrainBase::CreateMineralLayerEventHandler(FXLagDynamicTerrainMapItem* sender, const FXLagMineralDesc& mineral)
{
	auto size_x = Map->SizeX();
	auto size_y = Map->SizeY();

	auto SafeX = [&size_x](const int& x) { return x < 0 ? 0 : x >= size_x ? size_x - 1 : x; };
	auto SafeY = [&size_y](const int& y) { return y < 0 ? 0 : y >= size_y ? size_y - 1 : y; };

	auto mineralGenDesc = mineral.OccurrenceMineralGenDesc;

	if (mineralGenDesc.UnderTerrainElement != XLagDynamicTerrainMapItemOperation(*sender).GetTopKind()) // Проверяем условие залегания.
		return;

	auto coord = Map->GetCoordinate(sender);
	auto analystSize = 10;
	auto analystRect = CoordinateRect(SafeX(coord.X - analystSize), SafeY(coord.Y - analystSize),
		SafeX(coord.X + analystSize), SafeY(coord.Y + analystSize));

	float aroundMineralQuantity = 0.0f;

	for (int x = analystRect.Point1.X; x <= analystRect.Point2.X; x++)
		for (int y = analystRect.Point1.Y; y <= analystRect.Point2.Y; y++)
			aroundMineralQuantity += XLagDynamicTerrainMapItemOperation(Map->PointConst(x, y)).MeasureResourceQuantity(mineral.MineralTerrainElement);

	float currentMineralAvvarage = aroundMineralQuantity / analystRect.Square();

	if (currentMineralAvvarage != 0.0f/*> mineralGenDesc.AverageQuantity*/) // Если плотность минералов выше, то игнорируем генерацию.
		return;


	auto resurceRect = CoordinateRect(SafeX(coord.X - 3), SafeY(coord.Y - 3),
		SafeX(coord.X + 3), SafeY(coord.Y + 3));

	for (int x = resurceRect.Point1.X; x <= resurceRect.Point2.X; x++) // Делаем костыльное месторождение.
		for (int y = resurceRect.Point1.Y; y <= resurceRect.Point2.Y; y++)
		{
			auto item = XLagDynamicTerrainMapItemOperation(Map->Point(x, y));

			if (mineralGenDesc.UnderTerrainElement != TerrainElementEnum::None
				&& item.GetTopKind() != mineralGenDesc.UnderTerrainElement) // Проверяем условие верхнего элемента.
				continue;

			auto level = item.GetTopLevel();
			item.AddLayer(FXLagDynamicTerrainMapItemLayer(level - 10, mineral.MineralTerrainElement, mineral.ID));
			item.AddLayer(FXLagDynamicTerrainMapItemLayer(level - 200, TerrainElementEnum::RockBasalt));
			Map->Point(x, y).Changed = true;
		}
}

void AXLagDynamicTerrainBase::InitGeometry()
{

	XLagDynamicTerrainLayerGeometry _geometry;

	_geometry.CreateFrom(Map, TerrainElementEnum::GraundGrass);
	GenerateLayerGeometry(GroundGrass, &_geometry);

	_geometry.CreateFrom(Map, TerrainElementEnum::RockSandstone);
	GenerateLayerGeometry(RockSandstone, &_geometry);

	_geometry.CreateFrom(Map, TerrainElementEnum::RockBasalt);
	GenerateLayerGeometry(RockBasalt, &_geometry);

	_geometry.CreateFrom(Map, TerrainElementEnum::Coal);
	GenerateLayerGeometry(Coal, &_geometry);

	_geometry.CreateFrom(Map, TerrainElementEnum::Cultivated);
	GenerateLayerGeometry(Cultivated, &_geometry);

	_geometry.CreateTransFrom(Map, TerrainElementEnum::GroundGrassToRockSandstoneTrans, TerrainElementEnum::GraundGrass, TerrainElementEnum::RockSandstone);
	GenerateLayerGeometry(GroundGrassToRockSandstone, &_geometry);

	_geometry.CreateTransFrom(Map, TerrainElementEnum::GrondGrassToRockBasaltTrans, TerrainElementEnum::GraundGrass, TerrainElementEnum::RockBasalt);
	GenerateLayerGeometry(GroundGrassToRockBasalt, &_geometry);
	
	_geometry.CreateTransFrom(Map, TerrainElementEnum::GrondGrassToCoalTrans, TerrainElementEnum::GraundGrass, TerrainElementEnum::Coal);
	GenerateLayerGeometry(GroundGrassToCoal, &_geometry);

	_geometry.CreateTransFrom(Map, TerrainElementEnum::GrondGrassToCultivatedTrans, TerrainElementEnum::GraundGrass, TerrainElementEnum::Cultivated);
	GenerateLayerGeometry(GroundGrassToCultivated, &_geometry);


	_geometry.CreateTransFrom(Map, TerrainElementEnum::RockSandstoneToRockBasaltTrans, TerrainElementEnum::RockSandstone, TerrainElementEnum::RockBasalt);
	GenerateLayerGeometry(RockSandstoneToRockBasalt, &_geometry);

	InitGeometryForColorizeMap();
}

void AXLagDynamicTerrainBase::InitGeometryForColorizeMap()
{
	XLagColorizeMapGeometryBuilder _colorizeMapGeometry;

	if (IsActivatedColorizedMap)
	{
		_colorizeMapGeometry.CreateColorizeMap(Map);
	}
	
	GenerateLayerGeometry(ColorizeMapper, &_colorizeMapGeometry);
}

void AXLagDynamicTerrainBase::GenerateLayerGeometry(UProceduralMeshComponent* Component, GeometryBuilderAbstract* geometry)
{
	UE_LOG(LogTemp, Warning, TEXT("GenerateLayerGeometry"));
	Component->CreateMeshSection_LinearColor(0, geometry->Vertices, geometry->Trinagles, geometry->Normals, geometry->UVs, geometry->Colors, TArray<FProcMeshTangent>(), true);
}

void AXLagDynamicTerrainBase::AddGreader()
{
	return;
	float x = 5000; float y = 5000;
	float z = XLagDynamicTerrainMapItemOperation(Map->Point(50, 50)).Get()->Level + 10.f;

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
