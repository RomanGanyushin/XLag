#include "XLagDynamicTerrainLayerGeometry.h"

void XLagDynamicTerrainLayerGeometry::CreateFrom(std::shared_ptr<ITerrainMapAccessor> map, int layerKind)
{
	Reset();

	int32 triIndex = 0;

	for (int xIndex = 0; xIndex < map->SizeX() - 1; xIndex++)
		for (int yIndex = 0; yIndex < map->SizeY() -1; yIndex++)
		{
			auto& item00 = map->Point(xIndex, yIndex);
			auto& item10 = map->Point(xIndex + 1, yIndex);
			auto& item11 = map->Point(xIndex + 1, yIndex + 1);
			auto& item01 = map->Point(xIndex, yIndex + 1);

			auto itemLevel00 = item00.Get();
			auto itemLevel10 = item10.Get();
			auto itemLevel11 = item11.Get();
			auto itemLevel01 = item01.Get();

			if (itemLevel00 == nullptr || itemLevel10 == nullptr || itemLevel11 == nullptr || itemLevel01 == nullptr)
			{
				continue;
			}

			auto fl = itemLevel00->GetLevel(); auto k = itemLevel00->GetTerrainElement();
			if (k != layerKind)
				continue;

			AddQuadMesh(
				FVector(100 * xIndex, 100 * yIndex, itemLevel00->GetLevel()),
				FVector(100 * xIndex, 100 * (yIndex + 1), itemLevel01->GetLevel()),
				FVector(100 * (xIndex + 1), 100 * (yIndex + 1), itemLevel11->GetLevel()),
				FVector(100 * (xIndex + 1), 100 * yIndex, itemLevel10->GetLevel()),
				triIndex);
		}
}


void XLagDynamicTerrainLayerGeometry::CreateTransFrom(std::shared_ptr<ITerrainMapAccessor> map, int layerKind, int fromKind, int toKind)
{
	Reset();

	int32 triIndex = 0;

	for (int xIndex = 1; xIndex < map->SizeX() - 1; xIndex++)
		for (int yIndex = 1; yIndex < map->SizeY() - 1; yIndex++)
		{
			auto& item00 = map->Point(xIndex, yIndex);
			auto& item10 = map->Point(xIndex + 1, yIndex);
			auto& item11 = map->Point(xIndex + 1, yIndex + 1);
			auto& item01 = map->Point(xIndex, yIndex + 1);

			auto itemLevel00 = item00.Get();
			auto itemLevel10 = item10.Get();
			auto itemLevel11 = item11.Get();
			auto itemLevel01 = item01.Get();

			if (itemLevel00 == nullptr || itemLevel10 == nullptr || itemLevel11 == nullptr || itemLevel01 == nullptr)
			{
				continue;
			}

			auto k = itemLevel00->GetTerrainElement();
			
			if (k != layerKind)
				continue;

			AddQuadMesh(
				FVector(100 * xIndex, 100 * yIndex, itemLevel00->GetLevel()),
				FVector(100 * xIndex, 100 * (yIndex + 1), itemLevel01->GetLevel()),
				FVector(100 * (xIndex + 1), 100 * (yIndex + 1), itemLevel11->GetLevel()),
				FVector(100 * (xIndex + 1), 100 * yIndex, itemLevel10->GetLevel()),
				triIndex);

			float a1 = 0;
			float a2 = 0;
			float a3 = 0;
			float a4 = 0;

			if (map->Point(xIndex - 1, yIndex - 1).Get()->GetTerrainElement() == fromKind
				|| map->Point(xIndex - 1, yIndex).Get()->GetTerrainElement() == fromKind
				|| map->Point(xIndex, yIndex - 1).Get()->GetTerrainElement() == fromKind)
			{
				a1 = 0;
			}
			else if(map->Point(xIndex - 1, yIndex - 1).Get()->GetTerrainElement() == toKind
				|| map->Point(xIndex - 1, yIndex).Get()->GetTerrainElement() == toKind
				|| map->Point(xIndex, yIndex - 1).Get()->GetTerrainElement() == toKind)
			{
				a1 = 1;
			}
			else
			{
				a1 = 0.5;
			}

			if (map->Point(xIndex - 1, yIndex).Get()->GetTerrainElement() == fromKind
				|| map->Point(xIndex - 1, yIndex + 1).Get()->GetTerrainElement() == fromKind
				|| map->Point(xIndex, yIndex + 1).Get()->GetTerrainElement() == fromKind)
			{
				a2 = 0;
			}
			else if (map->Point(xIndex - 1, yIndex).Get()->GetTerrainElement() == toKind
				|| map->Point(xIndex - 1, yIndex + 1).Get()->GetTerrainElement() == toKind
				|| map->Point(xIndex, yIndex + 1).Get()->GetTerrainElement() == toKind)
			{
				a2 = 1;
			}
			else
			{
				a2 = 0.5;
			}

			if (map->Point(xIndex, yIndex + 1).Get()->GetTerrainElement() == fromKind
				|| map->Point(xIndex + 1, yIndex + 1).Get()->GetTerrainElement() == fromKind
				|| map->Point(xIndex + 1, yIndex).Get()->GetTerrainElement() == fromKind)
			{
				a3 = 0;
			}
			else if (map->Point(xIndex, yIndex + 1).Get()->GetTerrainElement() == toKind
				|| map->Point(xIndex + 1, yIndex + 1).Get()->GetTerrainElement() == toKind
				|| map->Point(xIndex + 1, yIndex).Get()->GetTerrainElement() == toKind)
			{
				a3 = 1;
			}
			else
			{
				a3 = 0.5;
			}

			if (map->Point(xIndex + 1, yIndex).Get()->GetTerrainElement() == fromKind
				|| map->Point(xIndex + 1, yIndex - 1).Get()->GetTerrainElement() == fromKind
				|| map->Point(xIndex, yIndex - 1).Get()->GetTerrainElement() == fromKind)
			{
				a4 = 0;
			}
			else if (map->Point(xIndex + 1, yIndex).Get()->GetTerrainElement() == toKind
				|| map->Point(xIndex + 1, yIndex - 1).Get()->GetTerrainElement() == toKind
				|| map->Point(xIndex, yIndex - 1).Get()->GetTerrainElement() == toKind)
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
