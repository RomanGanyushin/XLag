#pragma once
#include "GeometryBuilderAbstract.h"

// Компонет для гененерации геометрии земли.
class XLagMineralStackGeometryBuilder : public GeometryBuilderAbstract
{
public:
	void CreateMineralStack(float height);
};