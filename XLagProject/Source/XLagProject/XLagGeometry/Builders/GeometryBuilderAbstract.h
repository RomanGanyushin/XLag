#pragma once

class GeometryBuilderAbstract
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

	float UVScale = 400.0;

public:
	// ����������� ����������.
	virtual ~GeometryBuilderAbstract() = default;

protected:
	void Reset();
	void AddTriangleMesh(FVector p1, FVector p2, FVector p3, int32& triIndex);
	void AddQuadMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
	void AddQuadSMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
};