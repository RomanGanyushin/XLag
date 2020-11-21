#include "XLagLooseStackBase.h"
#include "../XLagDynamicObject/ObjectModels/TerrainLooseStackObject.h"
#include "XLagProject/XLagGeometry/Builders/XLagMineralStackGeometryBuilder.h"

AXLagLooseStackBase::AXLagLooseStackBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ThisStack = CreateDefaultSubobject<UProceduralMeshComponent>("Stack");
	ThisStack->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AXLagLooseStackBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXLagLooseStackBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLagLooseStackBase::AssignObject(const FXLagDynamicObject& object)
{
	AXLagSwapableObject::AssignObject(object);
	TerrainLooseStackObject stackProperties(*(const_cast<FXLagDynamicObject*>(&object)));
	StackQuantity = stackProperties.GetStackQuantity();
	
	const_cast<FXLagDynamicObject*>(&object)->PropertyChangedEvent.AddDynamic(this, &AXLagLooseStackBase::OnPropertyChanged);
}

void AXLagLooseStackBase::OnPropertyChanged(uint8 id, const FXLagObjectProperties& properties)
{
	TerrainLooseStackObject stackProperties(*(const_cast<FXLagObjectProperties*>(&properties)));

	if (id == LooseStackParameterId::ParId_StackQuantity)
	{
		auto quantity = stackProperties.GetStackQuantity();
		StackQuantity = quantity;
		CreateView();
	}
}


void AXLagLooseStackBase::AddQuantity(float quantity)
{
	StackQuantity += quantity;
	CreateView();
}

float AXLagLooseStackBase::GetAvaibleQuantity()
{
	float result = StackQuantity;
	for (auto& it : _reserves) result -= it.second;
	return result;
}

void AXLagLooseStackBase::Reserve(AXLagNPCBase *reserver, float quantity)
{
	_reserves[reserver] = quantity;
}

float AXLagLooseStackBase::TakeQuantity(AXLagNPCBase *npc, float quantity)
{
	if (!IsReservedFor(npc))
		return 0.0f;

	auto takeQuanity = std::min(_reserves[npc], quantity);
	_reserves[npc] = _reserves[npc] - takeQuanity;

	if (_reserves[npc] <= 0)
	{
		_reserves.erase(_reserves.find(npc));
	}

	StackQuantity -= takeQuanity;
	return takeQuanity;
}

bool AXLagLooseStackBase::IsReservedFor(const AXLagNPCBase *npc) const
{
	return _reserves.find(npc) != _reserves.end();
}

void AXLagLooseStackBase::CreateView()
{
	XLagMineralStackGeometryBuilder geometry;
	geometry.CreateMineralStack(StackQuantity, SizeX, SizeY);
	ThisStack->CreateMeshSection_LinearColor(0, geometry.Vertices, geometry.Trinagles, geometry.Normals, geometry.UVs, geometry.Colors, TArray<FProcMeshTangent>(), true);
}