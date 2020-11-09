#include "AligmentEditComponent.h"
#include "../../XLagDynamicTerrainMapItemOperation.h"

AligmentEditComponent::AligmentEditComponent(const AligmentEditComponentSettings& settings)
	: _settings(settings)
{
}

void AligmentEditComponent::PrepareForEdit(ITerrainMapAccessor *const accessor)
{
	if (accessor == nullptr)
	{
		return;
	}

	_level = XLagDynamicTerrainMapItemOperation(accessor->Point(_settings.RefXIndex, _settings.RefYIndex)).GetTopLevel();
}

void AligmentEditComponent::DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy)
{
	if (accessor == nullptr)
	{
		return;
	}

	auto dist = sqrt(std::pow(ix - _settings.RefXIndex, 2) + std::pow(iy - _settings.RefYIndex, 2));
	auto point = XLagDynamicTerrainMapItemOperation(accessor->Point(ix, iy));
	const auto level = point.GetTopLevel();

	if (dist <= _settings.ZeroPlaceRadius)
	{
		point.MoveTopLevelTo(_settings.ZeroLevel);
		accessor->Point(ix, iy).IsZeroLocation = true;
		return;
	}
	
	point.MoveTopLevelTo(point.GetTopLevel() - _level + _settings.ZeroLevel);

	if (dist <= _settings.ZeroPlaceRadius * 2)
	{
		auto newLevel = point.GetTopLevel() * (1.0f - (_settings.ZeroPlaceRadius * 2 - dist) / _settings.ZeroPlaceRadius);
		point.MoveTopLevelTo(newLevel);
	}

}
