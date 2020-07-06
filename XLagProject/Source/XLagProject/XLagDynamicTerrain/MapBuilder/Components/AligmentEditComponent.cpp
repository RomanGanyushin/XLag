#include "AligmentEditComponent.h"

AligmentEditComponent::AligmentEditComponent(const AligmentEditComponentSettings& settings)
	: _settings(settings)
{
}

void AligmentEditComponent::PrepareForEdit(ITerrainMapAccessor *const accessor)
{
	_level = accessor->Point(_settings.RefXIndex, _settings.RefYIndex).Get()->Level;
}

void AligmentEditComponent::DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy)
{
	auto dist = sqrt(std::pow(ix - _settings.RefXIndex, 2) + std::pow(iy - _settings.RefYIndex, 2));
	auto& point = accessor->Point(ix, iy);
	auto& level = point.Stack.back().Level;

	if (dist <= _settings.ZeroPlaceRadius)
	{
		level = _settings.ZeroLevel;
		point.IsZeroLocation = true;
		return;
	}
	
	level += -_level + _settings.ZeroLevel;
	
	if (dist <= _settings.ZeroPlaceRadius * 2)
	{
		level = level * (1.0f - (_settings.ZeroPlaceRadius * 2 - dist) / _settings.ZeroPlaceRadius);
	}
}