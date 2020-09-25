#pragma once
#include "CoordinatePoint.h"

struct CoordinateRect
{
	CoordinateRect(const CoordinatePoint& pt1, const CoordinatePoint& pt2)
		: Point1(pt1), Point2(pt2)
	{
	}

	CoordinateRect(const int& pt1x, const int& pt1y, const int& pt2x, const int& pt2y)
		: Point1(pt1x, pt1y), Point2(pt2x, pt2y)
	{
	}

	CoordinatePoint Point1;
	CoordinatePoint Point2;

	const int Square() const { return (Point2.X - Point1.X) * (Point2.Y - Point1.Y); }
};