#include "PerlinFillerMapEditComponent.h"
#include "../../XLagDynamicTerrainMapItemOperation.h"
#include <time.h>


PerlinFillerMapEditComponent::PerlinFillerMapEditComponent(
	const TerrainElementEnum element, 
	const PerlinFillerMapEditSettings settings)
	:_perlin2DAlgorithm(new Perlin2DAlgorithm(time(nullptr))),
	_element(element), _settings(settings)
{
}

PerlinFillerMapEditComponent::~PerlinFillerMapEditComponent()
{
	if (_perlin2DAlgorithm != nullptr)
	{
		delete _perlin2DAlgorithm;
		_perlin2DAlgorithm = nullptr;
	}
}

void PerlinFillerMapEditComponent::DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy)
{
	const auto level = _perlin2DAlgorithm->Noise(
		static_cast<float>(ix) / _settings.XDevider, 
		static_cast<float>(iy) / _settings.YDevider, _settings.Octaves) * _settings.Amplitude;

	XLagDynamicTerrainMapItemOperation(accessor->Point(ix, iy)).AddLayer(FXLagDynamicTerrainMapItemLayer(level, _element));
}