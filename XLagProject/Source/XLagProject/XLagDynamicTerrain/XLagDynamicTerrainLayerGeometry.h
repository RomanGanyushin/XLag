#pragma once
#include "XLagDynamicTerrainMap.h"

class XLagDynamicTerrainLayerGeometry
{
public:
//	XLagDynamicTerrainLayerGeometry();

	TArray<FVector> Vertices;
	TArray<int32> Trinagles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;

public:
	void CreateFrom(XLagDynamicTerrainMap* map, int layerKind, bool useColor);

private:
	void Reset();
	void AddQuadMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
};