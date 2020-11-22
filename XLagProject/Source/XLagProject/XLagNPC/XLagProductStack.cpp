#include "XLagProductStack.h"

void AXLagProductStack::Initialize(const FXLagProductionSchema& product, const int sizeX, const int sizeY)
{
	ContentProduct = product;
	SizeX = sizeX;
	SizeY = sizeY;

	if (product.ProductPresentation != nullptr)
	{
		ProductPresentMesh = product.ProductPresentation;
	}

	CreateView();
}

void AXLagProductStack::CreateView()
{
	if (StackQuantity <= 0)
		return;

	auto bounding = ProductPresentMesh->GetBoundingBox();
	float offset_z = 0; int counter = 0;
	
	for (int ilayer = 0; counter < StackQuantity; ilayer++)
	{
		if (ilayer % 2 == 1)
		{
			CreateOddLayer(offset_z, counter);
		}
		else
		{
			CreateEvenLayer(offset_z, counter);
		}
		
		offset_z += bounding.GetSize().Z;
	}	
}

void AXLagProductStack::CreateOddLayer(float offset_z, int& counter)
{
	auto bounding = ProductPresentMesh->GetBoundingBox();
	auto offset = -bounding.Min; offset.Z += offset_z;
	auto local_offset = offset;

	auto count_x = 100.0f / (bounding.GetSize().X + 2);
	auto count_y = 100.0f / (bounding.GetSize().Y + 2);

	for (int x = 0; x < count_x; x++)
	{
		for (int y = 0; y < count_y; y++)
		{
			auto element = NewObject<UStaticMeshComponent>(this);
			element->SetupAttachment(RootComponent);
			element->SetStaticMesh(ProductPresentMesh);
			element->SetRelativeRotation(FRotator(0, 0, 0));
			element->SetRelativeLocation(local_offset);
			element->RegisterComponent();
			_elements.Add_GetRef(element);

			local_offset.Y += (bounding.GetSize().Y + 2);

			if (counter++ >= StackQuantity)
				return;
		}

		local_offset.X += bounding.GetSize().X + 2;
		local_offset.Y = offset.Y;
	}
}

void AXLagProductStack::CreateEvenLayer(float offset_z, int& counter)
{
	auto bounding = ProductPresentMesh->GetBoundingBox();
	auto offset = -bounding.Min;
	offset.Z += offset_z;
	auto local_offset = offset;
	local_offset.X = offset.Y;
	local_offset.Y = offset.X;

	auto count_x = 100.0f / (bounding.GetSize().Y + 2);
	auto count_y = 100.0f / (bounding.GetSize().X + 2);

	for (int x = 0; x < count_x; x++)
	{
		for (int y = 0; y < count_y; y++)
		{
			auto element = NewObject<UStaticMeshComponent>(this);
			element->SetupAttachment(RootComponent);
			element->SetStaticMesh(ProductPresentMesh);
			element->SetRelativeRotation(FRotator(0, 90, 0));
			element->SetRelativeLocation(local_offset);
			element->RegisterComponent();
			_elements.Add_GetRef(element);

			local_offset.Y += (bounding.GetSize().X + 2);

			if (counter++ > StackQuantity)
				return;
		}

		local_offset.X += bounding.GetSize().Y + 2;
		local_offset.Y = offset.X;
	}
}

void AXLagProductStack::ResetView()
{
	for (UStaticMeshComponent *it : _elements)
	{
		it->UnregisterComponent();
		it->DestroyComponent();
	}

	_elements.Reset();
}