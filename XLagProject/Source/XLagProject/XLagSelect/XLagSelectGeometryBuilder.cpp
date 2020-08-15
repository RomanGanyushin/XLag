#include "XLagSelectGeometryBuilder.h"


void XLagSelectGeometryBuilder::CreateDefault()
{
	Reset();
	int32 triIndex = 0;

	AddQuadMesh(FVector(0, 0, 0), FVector(0, 1, 0), FVector(1, 1, 0), FVector(1, 0, 0), triIndex);
}

void XLagSelectGeometryBuilder::CreateSelection(std::shared_ptr<ITerrainMapAccessor>  select)
{
	Reset();

	int32 triIndex = 0;
	FVector quadVertext[4];

	for (int xIndex = 0; xIndex < select->SizeX(); xIndex++)
		for (int yIndex = 0; yIndex < select->SizeY(); yIndex++)
		{
			quadVertext[0] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftBottomPosition) + FVector(0, 0, 0.1);
			quadVertext[1] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftTopPosition) + FVector(0, 0, 0.1);
			quadVertext[2] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightTopPosition) + FVector(0, 0, 0.1);
			quadVertext[3] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightBottomPosition) + FVector(0, 0, 0.1);

			AddQuadMesh(quadVertext[0], quadVertext[1], quadVertext[2],  quadVertext[3], triIndex);
		}
}