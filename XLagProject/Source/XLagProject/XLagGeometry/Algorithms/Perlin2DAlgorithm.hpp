#pragma once

class Perlin2DAlgorithm
{
private:

	unsigned char *permutationTable;

public:
	
	Perlin2DAlgorithm(int seed = 0)
	{
		srand(seed);
		permutationTable = new unsigned char[1024];
		for (int i = 0; i < 1024; i++)
			permutationTable[i] = rand() % 255;
	}

	~Perlin2DAlgorithm()
	{
		delete[] permutationTable;
	}

 private:
	
	float* GetPseudoRandomGradientVector(int x, int y)
	{
		int v = (int)(((x * 1836311903) ^ (y * 2971215073) + 4807526976) & 1023);
		v = permutationTable[v] & 3;

		switch (v)
		{
		case 0:  return new float[2] {  1, 0 };
		case 1:  return new float[2] { -1, 0 };
		case 2:  return new float[2] {  0, 1 };
		default: return new float[2] {  0, -1 };
		}
	}

	static float QunticCurve(float t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	static float Lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	static float Dot(float* a, float* b)
	{
		return a[0] * b[0] + a[1] * b[1];
	}

public:

	float Noise(float fx, float fy)
	{
		int left = (int)floor(fx);
		int top = (int)floor(fy);
		float pointInQuadX = fx - left;
		float pointInQuadY = fy - top;

		auto topLeftGradient = GetPseudoRandomGradientVector(left, top);
		auto topRightGradient = GetPseudoRandomGradientVector(left + 1, top);
		auto bottomLeftGradient = GetPseudoRandomGradientVector(left, top + 1);
		auto bottomRightGradient = GetPseudoRandomGradientVector(left + 1, top + 1);

		auto distanceToTopLeft = new float[2] { pointInQuadX, pointInQuadY   };
		auto distanceToTopRight = new float[2] { pointInQuadX - 1, pointInQuadY   };
		auto distanceToBottomLeft = new float[2] { pointInQuadX, pointInQuadY - 1 };
		auto distanceToBottomRight = new float[2] { pointInQuadX - 1, pointInQuadY - 1 };

		float tx1 = Dot(distanceToTopLeft, topLeftGradient);
		float tx2 = Dot(distanceToTopRight, topRightGradient);
		float bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
		float bx2 = Dot(distanceToBottomRight, bottomRightGradient);

		pointInQuadX = QunticCurve(pointInQuadX);
		pointInQuadY = QunticCurve(pointInQuadY);

		float tx = Lerp(tx1, tx2, pointInQuadX);
		float bx = Lerp(bx1, bx2, pointInQuadX);
		float tb = Lerp(tx, bx, pointInQuadY);

		delete[]topLeftGradient;
		delete[]topRightGradient;
		delete[]bottomLeftGradient;
		delete[]bottomRightGradient;

		delete[]distanceToTopLeft;
		delete[]distanceToTopRight;
		delete[]distanceToBottomLeft;
		delete[]distanceToBottomRight;

		return tb;
	}

	float Noise(float fx, float fy, int octaves, float persistence = 0.5f)
	{
		float amplitude = 1;
		float max = 0;
		float result = 0;

		while (octaves-- > 0)
		{
			max += amplitude;
			result += Noise(fx, fy) * amplitude;
			amplitude *= persistence;
			fx *= 2;
			fy *= 2;
		}

		return result / max;
	}
};