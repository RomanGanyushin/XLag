#pragma once
#include "../../Common/ITerrainMapAccessor.h"
#include "GeometryBuilderAbstract.h"

// Компонет для гененерации геометрии земли.
class XLagDynamicTerrainLayerGeometry : public GeometryBuilderAbstract
{
public:
	/// <summary>
	/// Creates from.
	/// </summary>
	/// <param name="map">The map.</param>
	/// <param name="layerKind">Kind of the layer.</param>
	void CreateFrom(std::shared_ptr<ITerrainMapAccessor> map, int layerKind);
	void CreateTransFrom(std::shared_ptr<ITerrainMapAccessor>  map, int layerKind, int mainKind);
};