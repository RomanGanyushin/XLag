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
			quadVertext[0] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftBottomPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[1] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftTopPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[2] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightTopPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[3] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightBottomPosition) + FVector(0, 0, SurfaceOffset);

			AddQuadMesh(quadVertext[0], quadVertext[1], quadVertext[2],  quadVertext[3], triIndex);
		}
}

void XLagSelectGeometryBuilder::CreateSelection2(std::shared_ptr<ITerrainMapAccessor>  select)
{
	Reset();

	int32 triIndex = 0;
	FVector quadVertext[4];

	for (int xIndex = 0; xIndex < select->SizeX(); xIndex++)
		for (int yIndex = 0; yIndex < select->SizeY(); yIndex++)
		{
			quadVertext[0] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftBottomPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[1] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftTopPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[2] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightTopPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[3] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightBottomPosition) + FVector(0, 0, SurfaceOffset);

			auto& item = select->PointConst(xIndex, yIndex);
			float alf = item.CheckForKind(TerrainElementEnum::Coal) ? 1.0 : 0;

			Colors.Add(FLinearColor(1, 0, 0, alf));
			Colors.Add(FLinearColor(1, 0, 0, alf));
			Colors.Add(FLinearColor(1, 0, 0, alf));
			Colors.Add(FLinearColor(1, 0, 0, alf));

			AddQuadMesh(quadVertext[0], quadVertext[1], quadVertext[2], quadVertext[3], triIndex);
		}
}

void XLagSelectGeometryBuilder::CreateGrid(std::shared_ptr<ITerrainMapAccessor> select)
{
	Reset();

	int32 triIndex = 0;
	FVector quadVertext[4];

	for (int xIndex = 0; xIndex < select->SizeX(); xIndex++)
		for (int yIndex = 0; yIndex < select->SizeY(); yIndex++)
		{
			quadVertext[0] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftBottomPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[1] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftTopPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[2] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightTopPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[3] = select->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightBottomPosition) + FVector(0, 0, SurfaceOffset);

			AddQuadMesh(quadVertext[0], quadVertext[0] + FVector(2, 0, 0), quadVertext[1] + FVector(2, 0, 0), quadVertext[1], triIndex);
			AddQuadMesh(quadVertext[0], quadVertext[3] , quadVertext[3] + FVector(0, 2, 0), quadVertext[0] + FVector(0, 2, 0), triIndex);

			if (xIndex == select->SizeX() - 1)
			{
				AddQuadMesh(quadVertext[3], quadVertext[3] + FVector(2, 0, 0), quadVertext[2] + FVector(2, 0, 0), quadVertext[2], triIndex);
			}

			if (yIndex == select->SizeY() - 1)
			{
				AddQuadMesh(quadVertext[1], quadVertext[2], quadVertext[2] + FVector(0, 2, 0), quadVertext[1] + FVector(0, 2, 0), triIndex);
			}
		}
}