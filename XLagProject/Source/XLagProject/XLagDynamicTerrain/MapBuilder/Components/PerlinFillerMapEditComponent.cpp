#include "PerlinFillerMapEditComponent.h"
#include <time.h>


PerlinFillerMapEditComponent::PerlinFillerMapEditComponent(
	const TerrainElementEnum element, 
	const PerlinFillerMapEditSettings settings)
	:_settings(settings),
	_perlin2DAlgorithm(new Perlin2DAlgorithm(time(0))), _element(element)
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
	auto level = _perlin2DAlgorithm->Noise(
		(float)ix / _settings.XDevider, 
		(float)iy / _settings.YDevider, _settings.Octaves) * _settings.Amplitude;

	accessor->Point(ix, iy).AddLayer(TerrainMapItemLevel(level, _element));
}