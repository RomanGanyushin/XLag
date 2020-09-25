#include "XLagMineralStackGeometryBuilder.h"


void XLagMineralStackGeometryBuilder::CreateMineralStack(float height)
{
	Reset();
	int32 triIndex = 0;

	if (height <= 0.0f)
		return;

	if (height > 200)
		height = 200;

	float delta = height * 0.3;
	float f_lx = 200;
	float f_ly = 200;

	AddQuadMesh(FVector(0 + delta, 0 + delta, height), FVector(0 + delta, f_ly - delta, height), FVector(f_lx - delta, f_ly - delta, height), FVector(f_lx - delta, delta, height), triIndex);
	AddQuadMesh(FVector(0, 0, 0), FVector(0, f_ly, 0), FVector(delta, f_ly - delta, height), FVector(0 + delta, delta, height), triIndex);
	AddQuadMesh(FVector(0, f_ly, 0), FVector(f_lx, f_ly, 0), FVector(f_lx-delta, f_ly - delta, height), FVector(0 + delta, f_ly - delta, height), triIndex);
	AddQuadMesh(FVector(f_lx, f_ly, 0), FVector(f_lx, 0, 0), FVector(f_lx - delta, delta, height), FVector(f_lx - delta, f_ly - delta, height), triIndex);
	AddQuadMesh(FVector(f_lx, 0, 0), FVector(0, 0, 0), FVector(delta, delta, height), FVector(f_lx - delta, delta, height), triIndex);
}