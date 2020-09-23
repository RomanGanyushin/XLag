#pragma once
#include "../Common/ITerrainMapAccessor.h"
#include "../Abstracts/GeometryBuilderAbstract.h"

class XLagSelectGeometryBuilder : public GeometryBuilderAbstract
{
public:
	float SurfaceOffset = 1.f;

public:
	void CreateDefault();
	void CreateSelection(std::shared_ptr<ITerrainMapAccessor>  select);
	void CreateGrid(std::shared_ptr<ITerrainMapAccessor>  select);

	//
	void CreateSelection2(std::shared_ptr<ITerrainMapAccessor>  select);
};