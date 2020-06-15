#include "XLagDynamicTerrainLayerGeometry.h"

void XLagDynamicTerrainLayerGeometry::CreateFrom(XLagDynamicTerrainMap* map, int layerKind)
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


			//auto itemLevel00 = item00.Get();
			//auto itemLevel10 = item10.Get();
			//auto itemLevel11 = item11.Get();
			//auto itemLevel01 = item01.Get();

			//if (itemLevel00 == nullptr || itemLevel10 == nullptr || itemLevel11 == nullptr || itemLevel01 == nullptr)
			//{
			//	continue;
			//}

			//auto fl = itemLevel00->Level; auto k = itemLevel00->LayerKind;
			//if (itemLevel10->Level > fl)
			//{
			//	fl = itemLevel10->Level;
			//	k = itemLevel10->LayerKind;
			//}
			//if (itemLevel11->Level > fl)
			//{
			//	fl = itemLevel11->Level;
			//	k = itemLevel11->LayerKind;
			//}

			//if (itemLevel01->Level > fl)
			//{
			//	fl = itemLevel01->Level;
			//	k = itemLevel01->LayerKind;
			//}

			//if (k != layerKind)
			//	continue;
			

			auto itemLevel00 = item00.Get();
			auto itemLevel10 = item10.Get();
			auto itemLevel11 = item11.Get();
			auto itemLevel01 = item01.Get();

			if (itemLevel00 == nullptr || itemLevel10 == nullptr || itemLevel11 == nullptr || itemLevel01 == nullptr)
			{
				continue;
			}

			auto fl = itemLevel00->Level; auto k = itemLevel00->LayerKind;
			if (itemLevel10->Level > fl)
			{
				fl = itemLevel10->Level;
				k = itemLevel10->LayerKind;
			}
			if (itemLevel11->Level > fl)
			{
				fl = itemLevel11->Level;
				k = itemLevel11->LayerKind;
			}

			if (itemLevel01->Level > fl)
			{
				fl = itemLevel01->Level;
				k = itemLevel01->LayerKind;
			}

			if (k != layerKind)
				continue;
			


			AddQuadMesh(
				FVector(100 * xIndex, 100 * yIndex, itemLevel00->Level),
				FVector(100 * xIndex, 100 * (yIndex + 1), itemLevel01->Level),
				FVector(100 * (xIndex + 1), 100 * (yIndex + 1), itemLevel11->Level),
				FVector(100 * (xIndex + 1), 100 * yIndex, itemLevel10->Level),
				triIndex);
		}
}

void XLagDynamicTerrainLayerGeometry::AddQuadMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex)
{
	Vertices.Add(p1);	Vertices.Add(p2);
	Vertices.Add(p3);   Vertices.Add(p4);

	Trinagles.Add(triIndex);
	Trinagles.Add(triIndex + 1);
	Trinagles.Add(triIndex + 2);
	Trinagles.Add(triIndex);
	Trinagles.Add(triIndex + 2);
	Trinagles.Add(triIndex + 3);

	triIndex += 4;

	/*auto ThisNorm = FVector::CrossProduct(p4 - p1, p2 - p1).GetSafeNormal();

	for (int i = 0; i < 4; i++)
	{
		Normals.Add(ThisNorm);
	}*/

	auto ThisNorm1 = FVector::CrossProduct(p3 - p1, p2 - p1).GetSafeNormal();
	auto ThisNorm2 = FVector::CrossProduct(p4 - p1, p4 - p1).GetSafeNormal();

	Normals.Add(ThisNorm1);
	Normals.Add(ThisNorm1);
	Normals.Add(ThisNorm1);
	Normals.Add(ThisNorm2);

	UVs.Add(FVector2D(0.f, 0.f));
	UVs.Add(FVector2D(0.f, 1.f));
	UVs.Add(FVector2D(1.f, 1.f));
	UVs.Add(FVector2D(1.f, 0.f));
}

void XLagDynamicTerrainLayerGeometry::Reset()
{
	Vertices.Reset();
	Trinagles.Reset();
	Normals.Reset();
	UVs.Reset();
}