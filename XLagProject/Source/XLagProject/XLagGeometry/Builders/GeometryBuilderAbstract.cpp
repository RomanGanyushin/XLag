#include "GeometryBuilderAbstract.h"

void GeometryBuilderAbstract::AddTriangleMesh(FVector p1, FVector p2, FVector p3, int32& triIndex)
{
	Vertices.Add(p1);	Vertices.Add(p2); Vertices.Add(p3);   

	Trinagles.Add(triIndex);
	Trinagles.Add(triIndex + 1);
	Trinagles.Add(triIndex + 2);

	triIndex += 3;

	auto ThisNorm = FVector::CrossProduct(p3 - p1, p2 - p1).GetSafeNormal();

	Normals.Add(ThisNorm);
	Normals.Add(ThisNorm);
	Normals.Add(ThisNorm);

	auto vx1 = p1.X / UVScale; auto vy1 = p1.Y / UVScale;
	auto vx2 = p2.X / UVScale; auto vy2 = p2.Y / UVScale;
	auto vx3 = p3.X / UVScale; auto vy3 = p3.Y / UVScale;
	UVs.Add(FVector2D(vx1, vy1));
	UVs.Add(FVector2D(vx2, vy2));
	UVs.Add(FVector2D(vx3, vy3));
}

void GeometryBuilderAbstract::AddQuadMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex)
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

	auto vx1 = p1.X / UVScale; auto vy1 = p1.Y / UVScale;
	auto vx2 = p2.X / UVScale; auto vy2 = p2.Y / UVScale;
	auto vx3 = p3.X / UVScale; auto vy3 = p3.Y / UVScale;
	auto vx4 = p4.X / UVScale; auto vy4 = p4.Y / UVScale;
	UVs.Add(FVector2D(vx1, vy1));
	UVs.Add(FVector2D(vx2, vy2));
	UVs.Add(FVector2D(vx3, vy3));
	UVs.Add(FVector2D(vx4, vy4));
}


void GeometryBuilderAbstract::Reset()
{
	Vertices.Reset();
	Trinagles.Reset();
	Normals.Reset();
	UVs.Reset();
	Colors.Reset();
}