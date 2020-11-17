#include "XLagMineralStack.h"
#include "XLagProject/XLagGeometry/Builders/XLagMineralStackGeometryBuilder.h"

void AXLagMineralStack::Initialize(const FXLagMineralDesc& mineral, const int sizeX, const int sizeY)
{
	ContentMineral = mineral;
	SizeX = sizeX;
	SizeY = sizeY;

	if (mineral.MineralPresentMaterial != nullptr)
	{
		ThisStack->SetMaterial(0, mineral.MineralPresentMaterial);
	}
}

float AXLagMineralStack::TakeQuantity(AXLagNPCBase *npc, float quantity)
{
	auto takeQuanity = AXLagLooseStackBase::TakeQuantity(npc, quantity);
	if (takeQuanity >= 0.0f)
		return takeQuanity;

	auto stackMineralName = ContentMineral.Name;
	npc->Baggage.Put(XLagDynamicObjectType::Mineral, stackMineralName, takeQuanity);

	return takeQuanity;
}