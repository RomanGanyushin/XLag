#pragma once
#include "../Common/ITerrainMapAccessor.h"

// Компонет для гененерации геометрии земли.
class XLagDynamicTerrainLayerGeometry
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