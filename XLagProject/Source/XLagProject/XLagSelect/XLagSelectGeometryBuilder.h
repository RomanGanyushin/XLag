#pragma once
#include "../Common/ITerrainMapAccessor.h"
#include "../Abstracts/GeometryBuilderAbstract.h"

class XLagSelectGeometryBuilder : public GeometryBuilderAbstract
{
public:
	void CreateDefault();
	void CreateSelection(std::shared_ptr<ITerrainMapAccessor>  select);
};