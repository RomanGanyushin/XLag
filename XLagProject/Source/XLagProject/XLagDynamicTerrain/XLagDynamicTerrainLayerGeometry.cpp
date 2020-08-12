#include "XLagDynamicTerrainLayerGeometry.h"

void XLagDynamicTerrainLayerGeometry::CreateDefault()
{
	Reset();
	int32 triIndex = 0;

	AddQuadMesh( FVector(0,0,0), FVector(0,1,0), FVector(1,1,0), FVector(1,0,0), triIndex);
}

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

			auto fl = itemLevel00->GetLevel(); auto k = itemLevel00->GetKind();
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

			auto fl = itemLevel00->GetLevel(); auto k = itemLevel00->GetKind();
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

			if (map->Point(xIndex - 1, yIndex).Get()->GetKind() == mainKind)
			{
				a1 = a2 = 0;
			}


			if (map->Point(xIndex, yIndex + 1).Get()->GetKind() == mainKind)
			{
				a2 = a3 = 0;
			}

			if (map->Point(xIndex + 1, yIndex).Get()->GetKind() == mainKind)
			{
				a3 = a4 = 0;
			}

			if (map->Point(xIndex, yIndex - 1).Get()->GetKind() == mainKind)
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

void XLagDynamicTerrainLayerGeometry::CreateSelection(std::shared_ptr<ITerrainMapAccessor>  map)
{
	Reset();

	int32 triIndex = 0;

	for (int xIndex = 50; xIndex < 55; xIndex++)
		for (int yIndex = 50; yIndex < 55; yIndex++)
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

			AddQuadMesh(
				FVector(100 * xIndex, 100 * yIndex, itemLevel00->GetLevel() + 0.1),
				FVector(100 * xIndex, 100 * (yIndex + 1), itemLevel01->GetLevel() + 0.1),
				FVector(100 * (xIndex + 1), 100 * (yIndex + 1), itemLevel11->GetLevel() + 0.1),
				FVector(100 * (xIndex + 1), 100 * yIndex, itemLevel10->GetLevel() + 0.1),
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

	auto ThisNorm1 = FVector::CrossProduct(p3 - p1, p2 - p1);
	auto ThisNorm2 = FVector::CrossProduct(p3 - p1, p2 - p1);
	auto ThisNorm3 = FVector::CrossProduct(p4 - p1, p4 - p1);
	auto ThisNorm4 = FVector::CrossProduct(p3 - p1, p2 - p1);

	Normals.Add(ThisNorm1.GetSafeNormal());
	Normals.Add(ThisNorm2.GetSafeNormal());
	Normals.Add(ThisNorm3.GetSafeNormal());
	Normals.Add(ThisNorm4.GetSafeNormal());

	auto vx1 = p1.X / 400.f; auto vy1 = p1.Y / 400.f;
	auto vx2 = p2.X / 400.f; auto vy2 = p2.Y / 400.f;
	auto vx3 = p3.X / 400.f; auto vy3 = p3.Y / 400.f;
	auto vx4 = p4.X / 400.f; auto vy4 = p4.Y / 400.f;
	UVs.Add(FVector2D(vx1, vy1));
	UVs.Add(FVector2D(vx2, vy2));
	UVs.Add(FVector2D(vx3, vy3));
	UVs.Add(FVector2D(vx4, vy4));
}

void XLagDynamicTerrainLayerGeometry::AddQuadSMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex)
{
	auto center = (p1 + p2 + p3 + p4) / 4;

	Vertices.Add(center);
	Vertices.Add(p1);	Vertices.Add(p2);
	Vertices.Add(p3);   Vertices.Add(p4);

	Trinagles.Add(triIndex + 1);
	Trinagles.Add(triIndex + 2);
	Trinagles.Add(triIndex);
	Trinagles.Add(triIndex + 2);
	Trinagles.Add(triIndex + 3);
	Trinagles.Add(triIndex);
	Trinagles.Add(triIndex + 3);
	Trinagles.Add(triIndex + 4);
	Trinagles.Add(triIndex);
	Trinagles.Add(triIndex + 4);
	Trinagles.Add(triIndex + 1);
	Trinagles.Add(triIndex);

	triIndex +=5;

	auto ThisNorm1 = FVector::CrossProduct(p3 - p1, p2 - p1);
	auto ThisNorm2 = FVector::CrossProduct(p3 - p1, p2 - p1);
	auto ThisNorm3 = FVector::CrossProduct(p4 - p1, p4 - p1);
	auto ThisNorm4 = FVector::CrossProduct(p3 - p1, p2 - p1);
 // TODO доделать

	Normals.Add(ThisNorm1.GetSafeNormal());
	Normals.Add(ThisNorm1.GetSafeNormal());
	Normals.Add(ThisNorm2.GetSafeNormal());
	Normals.Add(ThisNorm3.GetSafeNormal());
	Normals.Add(ThisNorm4.GetSafeNormal());

	auto vx1 = p1.X / 400.f; auto vy1 = p1.Y / 400.f;
	auto vx2 = p2.X / 400.f; auto vy2 = p2.Y / 400.f;
	auto vx3 = p3.X / 400.f; auto vy3 = p3.Y / 400.f;
	auto vx4 = p4.X / 400.f; auto vy4 = p4.Y / 400.f;
	auto vx = (vx1 + vx2 + vx3 + vx4) / 4; auto vy = (vy1 + vy2 + vy3 + vy4) / 4;
	UVs.Add(FVector2D(vx, vy));
	UVs.Add(FVector2D(vx1, vy1));
	UVs.Add(FVector2D(vx2, vy2));
	UVs.Add(FVector2D(vx3, vy3));
	UVs.Add(FVector2D(vx4, vy4));
}

void XLagDynamicTerrainLayerGeometry::Reset()
{
	Vertices.Reset();
	Trinagles.Reset();
	Normals.Reset();
	UVs.Reset();
	Colors.Reset();
}