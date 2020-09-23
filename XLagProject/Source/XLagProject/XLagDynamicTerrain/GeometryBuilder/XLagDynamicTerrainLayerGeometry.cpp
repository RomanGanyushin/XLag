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

void XLagDynamicTerrainLayerGeometry::CreateTransFrom(std::shared_ptr<ITerrainMapAccessor> map, int layerKind, int mainKind)
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

			auto fl = itemLevel00->GetLevel(); auto k = itemLevel00->GetTerrainElement();
			if (k != layerKind)
				continue;



			AddQuadSMesh(
				FVector(100 * xIndex, 100 * yIndex, itemLevel00->GetLevel()),
				FVector(100 * xIndex, 100 * (yIndex + 1), itemLevel01->GetLevel()),
				FVector(100 * (xIndex + 1), 100 * (yIndex + 1), itemLevel11->GetLevel()),
				FVector(100 * (xIndex + 1), 100 * yIndex, itemLevel10->GetLevel()),
				triIndex);

			float a1 = 1;
			float a2 = 1;
			float a3 = 1;
			float a4 = 1;

			if (map->Point(xIndex - 1, yIndex).Get()->GetTerrainElement() == mainKind)
			{
				a1 = a2 = 0;
			}


			if (map->Point(xIndex, yIndex + 1).Get()->GetTerrainElement() == mainKind)
			{
				a2 = a3 = 0;
			}

			if (map->Point(xIndex + 1, yIndex).Get()->GetTerrainElement() == mainKind)
			{
				a3 = a4 = 0;
			}

			if (map->Point(xIndex, yIndex - 1).Get()->GetTerrainElement() == mainKind)
			{
				a4 = a1 = 0;
			}

			Colors.Add(FLinearColor(1, 1, 1, 1));		
			Colors.Add(FLinearColor(a1, a1, a1, a1));
			Colors.Add(FLinearColor(a2, a2, a2, a2));
			Colors.Add(FLinearColor(a3, a3, a3, a3));
			Colors.Add(FLinearColor(a4, a4, a4, a4));			
		}
}