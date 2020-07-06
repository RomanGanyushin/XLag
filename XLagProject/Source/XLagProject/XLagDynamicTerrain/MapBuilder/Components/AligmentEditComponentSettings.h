#pragma once

struct AligmentEditComponentSettings
{
	AligmentEditComponentSettings(const int& ref_ix, const int& ref_iy, const double&  zeroR, const double zeroL)
		:RefXIndex(ref_ix), RefYIndex(ref_iy), ZeroPlaceRadius(zeroR), ZeroLevel(zeroL)
	{
	}
	const int RefXIndex;
	const int RefYIndex;
	const double ZeroPlaceRadius;
	const double ZeroLevel;
};
