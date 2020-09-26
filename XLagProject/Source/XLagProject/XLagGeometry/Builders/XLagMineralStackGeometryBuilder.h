#pragma once
#include "GeometryBuilderAbstract.h"

// Компонет для гененерации геометрии земли.
class XLagMineralStackGeometryBuilder : public GeometryBuilderAbstract
{
public:
	void CreateMineralStack(float height, int size_x, int size_y, float delta = 0.1, float octaves = 2);
};