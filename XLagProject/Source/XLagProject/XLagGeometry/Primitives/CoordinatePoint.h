#pragma once

struct CoordinatePoint
{
	CoordinatePoint(const int &x, const int &y)
	: X(x),Y(y)
	{
	}

	int X;
	int Y;
};