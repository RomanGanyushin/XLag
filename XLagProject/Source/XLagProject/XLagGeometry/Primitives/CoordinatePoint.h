#pragma once

struct CoordinatePoint
{
	CoordinatePoint()
		: X(0), Y(0) 
	{
	}

	CoordinatePoint(const int &x, const int &y)
	: X(x),Y(y)
	{
	}

	int X;
	int Y;

	bool IsEqual(const CoordinatePoint& pt) const
	{
		return pt.X == X && Y == pt.Y;
	}
};


