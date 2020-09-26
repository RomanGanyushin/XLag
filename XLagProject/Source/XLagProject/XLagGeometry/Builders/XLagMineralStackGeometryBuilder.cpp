#include "XLagMineralStackGeometryBuilder.h"
#include "../Algorithms/Perlin2DAlgorithm.hpp"

void XLagMineralStackGeometryBuilder::CreateMineralStack(float height, int size_x, int size_y, float delta, float octaves)
{	
	if (height <= 0.0f)
		return;

	if (height > 200)
		height = 200;
	
	Reset();
	int32 triIndex = 0;

	Perlin2DAlgorithm alg(height);
	
	auto zeroEdgeFunction = [octaves](const float& ax, const float& ay)
	{
		return sin(3.1415 / octaves * ax) * sin(3.1415 / octaves * ay);
	};

	auto heightFunction = [height, &alg, octaves, zeroEdgeFunction](const float& ax, const float& ay)
	{
		return height * (1 + alg.Noise(ax, ay, octaves, 1)) * zeroEdgeFunction(ax, ay);
	};
	
	for (float ax = 0; ax < octaves; ax+= delta)
		for (float ay = 0; ay < octaves; ay+= delta)
		{
			float h00 = heightFunction(ax,ay);
			float h01 = heightFunction(ax, ay + delta);
			float h11 = heightFunction(ax + delta, ay + delta);
			float h10 = heightFunction(ax + delta, ay);

			auto v1 = FVector(size_x * 100.0 / octaves * (ax), size_y * 100.0 / octaves * (ay), h00);
			auto v2 = FVector(size_x * 100.0 / octaves * (ax), size_y * 100.0 / octaves * (ay + delta), h01);
			auto v3 = FVector(size_x * 100.0 / octaves * (ax + delta), size_y * 100.0 / octaves * (ay + delta), h11);
			auto v4 = FVector(size_x * 100.0 / octaves * (ax + delta), size_y * 100.0 / octaves * (ay), h10);
			
			AddQuadMesh(v1, v2, v3, v4, triIndex);
		}
}