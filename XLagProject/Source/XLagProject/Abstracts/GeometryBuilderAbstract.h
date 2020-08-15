#pragma once

class GeometryBuilderAbstract
{
public:
	// Массив вершин.
	TArray<FVector> Vertices;

	// Массив индексов вершин треуголникаов.
	TArray<int32> Trinagles;

	// Массив нормалей к вершинам треугольников.
	TArray<FVector> Normals;

	// Массиа координат текстурных.
	TArray<FVector2D> UVs;

	// Массив описыващий цвета вершин.
	TArray<FLinearColor> Colors;

public:
	// Виртуальный деструктор.
	virtual ~GeometryBuilderAbstract() = default;

protected:
	void Reset();
	void AddQuadMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
	void AddQuadSMesh(FVector p1, FVector p2, FVector p3, FVector p4, int32& triIndex);
};