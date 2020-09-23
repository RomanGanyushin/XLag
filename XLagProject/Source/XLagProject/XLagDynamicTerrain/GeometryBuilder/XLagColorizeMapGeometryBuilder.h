#pragma once

#pragma once
#include "../../Common/ITerrainMapAccessor.h"
#include "../../Abstracts/GeometryBuilderAbstract.h"

// Компонет для гененерации геометрии земли.
class XLagColorizeMapGeometryBuilder : public GeometryBuilderAbstract
{
public:
	float SurfaceOffset = 1.f;
public:
	void CreateColorizeMap(std::shared_ptr<ITerrainMapAccessor> map);
};