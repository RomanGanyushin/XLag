#include "XLagMineralStack.h"
#include "XLagProject/XLagGeometry/Builders/XLagMineralStackGeometryBuilder.h"

// Sets default values
AXLagMineralStack::AXLagMineralStack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MineralStack = CreateDefaultSubobject<UProceduralMeshComponent>("MineralStack");
	MineralStack->SetupAttachment(RootComponent);
	CreateView();
}

// Called when the game starts or when spawned
void AXLagMineralStack::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXLagMineralStack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLagMineralStack::Initialize(const FXLagMineralDesc& mineral, const int sizeX, const int sizeY)
{
	ContentMineral = mineral;
	SizeX = sizeX;
	SizeY = sizeY;

	if (mineral.MineralPresentMaterial != nullptr)
	{
		MineralStack->SetMaterial(0, mineral.MineralPresentMaterial);
	}
}

void AXLagMineralStack::AddMineral(float quantity) 
{
	MineralQuantity += quantity;
	CreateView();
}

void AXLagMineralStack::CreateView()
{
	XLagMineralStackGeometryBuilder geometry;
	geometry.CreateMineralStack(MineralQuantity, SizeX, SizeY);
	MineralStack->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
}