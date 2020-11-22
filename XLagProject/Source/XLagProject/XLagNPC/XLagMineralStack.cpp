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

	CreateView();
}