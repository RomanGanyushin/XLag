#include "XLagColorizeMapGeometryBuilder.h"
#include "../../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"

void XLagColorizeMapGeometryBuilder::CreateColorizeMap(std::shared_ptr<ITerrainMapAccessor> map)
{
	Reset();

	int32 triIndex = 0;
	FVector quadVertext[4];

	for (int xIndex = 0; xIndex < map->SizeX(); xIndex++)
		for (int yIndex = 0; yIndex < map->SizeY(); yIndex++)
		{
			quadVertext[0] = map->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftBottomPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[1] = map->GetWorldPosition(xIndex, yIndex, GetPositionEnum::LeftTopPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[2] = map->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightTopPosition) + FVector(0, 0, SurfaceOffset);
			quadVertext[3] = map->GetWorldPosition(xIndex, yIndex, GetPositionEnum::RightBottomPosition) + FVector(0, 0, SurfaceOffset);

			auto& item = map->PointConst(xIndex, yIndex);
			float alf = XLagDynamicTerrainMapItemOperation(item).CheckForMineral(4) ? 1.0 : 0;

			Colors.Add(FLinearColor(1, 0, 0, alf));
			Colors.Add(FLinearColor(1, 0, 0, alf));
			Colors.Add(FLinearColor(1, 0, 0, alf));
			Colors.Add(FLinearColor(1, 0, 0, alf));

			AddQuadMesh(quadVertext[0], quadVertext[1], quadVertext[2], quadVertext[3], triIndex);
		}
}