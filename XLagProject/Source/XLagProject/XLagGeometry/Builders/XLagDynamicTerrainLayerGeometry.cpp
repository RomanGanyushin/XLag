#include "XLagDynamicTerrainLayerGeometry.h"
#include "../../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"

void XLagDynamicTerrainLayerGeometry::CreateFrom(std::shared_ptr<ITerrainMapAccessor> map, int layerKind)
{
	Reset();

	int32 triIndex = 0;

	auto off_x = map->OffsetX() * 100;
	auto off_y = map->OffsetY() * 100;

	for (int xIndex = 0; xIndex < map->SizeX(); xIndex++)
		for (int yIndex = 0; yIndex < map->SizeY(); yIndex++)
		{
			if (!map->Validate(xIndex + 1, yIndex + 1))
				continue;

			auto& item00 = map->Point(xIndex, yIndex);
			auto& item10 = map->Point(xIndex + 1, yIndex);
			auto& item11 = map->Point(xIndex + 1, yIndex + 1);
			auto& item01 = map->Point(xIndex, yIndex + 1);

			auto itemLevel00 = XLagDynamicTerrainMapItemOperation(item00).Get();
			auto itemLevel10 = XLagDynamicTerrainMapItemOperation(item10).Get();
			auto itemLevel11 = XLagDynamicTerrainMapItemOperation(item11).Get();
			auto itemLevel01 = XLagDynamicTerrainMapItemOperation(item01).Get();

			if (itemLevel00 == nullptr || itemLevel10 == nullptr || itemLevel11 == nullptr || itemLevel01 == nullptr)
			{
				continue;
			}

			auto fl = itemLevel00->Level; auto k = itemLevel00->Element;
			if (k != layerKind)
				continue;

			AddQuadMesh(  
				FVector(off_x + 100 * xIndex, off_y+ 100 * yIndex, itemLevel00->Level),
				FVector(off_x + 100 * xIndex, off_y + 100 * (yIndex + 1), itemLevel01->Level),
				FVector(off_x + 100 * (xIndex + 1), off_y + 100 * (yIndex + 1), itemLevel11->Level),
				FVector(off_x + 100 * (xIndex + 1), off_y + 100 * yIndex, itemLevel10->Level),
				triIndex);
		}
}


void XLagDynamicTerrainLayerGeometry::CreateTransFrom(std::shared_ptr<ITerrainMapAccessor> map, int layerKind, int fromKind, int toKind)
{
	Reset();

	int32 triIndex = 0;

	auto off_x = map->OffsetX() * 100;
	auto off_y = map->OffsetY() * 100;

	for (int xIndex = 1; xIndex < map->SizeX(); xIndex++)
		for (int yIndex = 1; yIndex < map->SizeY(); yIndex++)
		{
			if (!map->Validate(xIndex + 1, yIndex + 1))
				continue;

			auto& item00 = map->Point(xIndex, yIndex);
			auto& item10 = map->Point(xIndex + 1, yIndex);
			auto& item11 = map->Point(xIndex + 1, yIndex + 1);
			auto& item01 = map->Point(xIndex, yIndex + 1);

			auto itemLevel00 = XLagDynamicTerrainMapItemOperation(item00).Get();
			auto itemLevel10 = XLagDynamicTerrainMapItemOperation(item10).Get();
			auto itemLevel11 = XLagDynamicTerrainMapItemOperation(item11).Get();
			auto itemLevel01 = XLagDynamicTerrainMapItemOperation(item01).Get();

			if (itemLevel00 == nullptr || itemLevel10 == nullptr || itemLevel11 == nullptr || itemLevel01 == nullptr)
			{
				continue;
			}

			auto k = itemLevel00->Element;
			
			if (k != layerKind)
				continue;

			AddQuadMesh(
				FVector(off_x + 100 * xIndex, off_y + 100 * yIndex, itemLevel00->Level),
				FVector(off_x + 100 * xIndex, off_y + 100 * (yIndex + 1), itemLevel01->Level),
				FVector(off_x + 100 * (xIndex + 1), off_y + 100 * (yIndex + 1), itemLevel11->Level),
				FVector(off_x + 100 * (xIndex + 1), off_y + 100 * yIndex, itemLevel10->Level),
				triIndex);

			float a1 = 0;
			float a2 = 0;
			float a3 = 0;
			float a4 = 0;

			if (XLagDynamicTerrainMapItemOperation(map->Point(xIndex - 1, yIndex - 1)).Get()->Element == fromKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex - 1, yIndex)).Get()->Element == fromKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex, yIndex - 1)).Get()->Element == fromKind)
			{
				a1 = 0;
			}
			else if(XLagDynamicTerrainMapItemOperation(map->Point(xIndex - 1, yIndex - 1)).Get()->Element == toKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex - 1, yIndex)).Get()->Element == toKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex, yIndex - 1)).Get()->Element == toKind)
			{
				a1 = 1;
			}
			else
			{
				a1 = 0.5;
			}

			if (XLagDynamicTerrainMapItemOperation(map->Point(xIndex - 1, yIndex)).Get()->Element == fromKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex - 1, yIndex + 1)).Get()->Element == fromKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex, yIndex + 1)).Get()->Element == fromKind)
			{
				a2 = 0;
			}
			else if (XLagDynamicTerrainMapItemOperation(map->Point(xIndex - 1, yIndex)).Get()->Element == toKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex - 1, yIndex + 1)).Get()->Element == toKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex, yIndex + 1)).Get()->Element == toKind)
			{
				a2 = 1;
			}
			else
			{
				a2 = 0.5;
			}

			if (XLagDynamicTerrainMapItemOperation(map->Point(xIndex, yIndex + 1)).Get()->Element == fromKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex + 1, yIndex + 1)).Get()->Element == fromKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex + 1, yIndex)).Get()->Element == fromKind)
			{
				a3 = 0;
			}
			else if (XLagDynamicTerrainMapItemOperation(map->Point(xIndex, yIndex + 1)).Get()->Element == toKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex + 1, yIndex + 1)).Get()->Element == toKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex + 1, yIndex)).Get()->Element == toKind)
			{
				a3 = 1;
			}
			else
			{
				a3 = 0.5;
			}

			if (XLagDynamicTerrainMapItemOperation(map->Point(xIndex + 1, yIndex)).Get()->Element == fromKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex + 1, yIndex - 1)).Get()->Element == fromKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex, yIndex - 1)).Get()->Element == fromKind)
			{
				a4 = 0;
			}
			else if (XLagDynamicTerrainMapItemOperation(map->Point(xIndex + 1, yIndex)).Get()->Element == toKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex + 1, yIndex - 1)).Get()->Element == toKind
				|| XLagDynamicTerrainMapItemOperation(map->Point(xIndex, yIndex - 1)).Get()->Element == toKind)
			{
				a4 = 1;
			}
			else
			{
				a4 = 0.5;
			}

			Colors.Add(FLinearColor(a1, a1, a1, a1));
			Colors.Add(FLinearColor(a2, a2, a2, a2));
			Colors.Add(FLinearColor(a3, a3, a3, a3));
			Colors.Add(FLinearColor(a4, a4, a4, a4));			
		}
}
