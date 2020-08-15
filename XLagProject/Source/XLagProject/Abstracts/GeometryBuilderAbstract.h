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

public:
	// ����������� ����������.
	virtual ~GeometryBuilderAbstract() = default;

protected:
	void Reset();
	void AddQuadMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
	void AddQuadSMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
};