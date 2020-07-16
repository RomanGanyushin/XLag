#pragma once
#include "../Common/ITerrainMapAccessor.h"

// �������� ��� ����������� ��������� �����.
class XLagDynamicTerrainLayerGeometry
{
public:
	// ������ ������.
	TArray<FVector> Vertices;

	// ������ �������� ������ �������������.
	TArray<int32> Trinagles;

	// ������ �������� � �������� �������������.
	TArray<FVector> Normals;

	// ������ ��������� ����������.
	TArray<FVector2D> UVs;

	// ������ ���������� ����� ������.
	TArray<FLinearColor> Colors;

public:
	/// <summary>
	/// Creates from.
	/// </summary>
	/// <param name="map">The map.</param>
	/// <param name="layerKind">Kind of the layer.</param>
	void CreateFrom(std::shared_ptr<ITerrainMapAccessor> map, int layerKind);
	void CreateTransFrom(std::shared_ptr<ITerrainMapAccessor>  map, int layerKind, int mainKind);

private:
	void Reset();
	void AddQuadMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
	void AddQuadSMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
};