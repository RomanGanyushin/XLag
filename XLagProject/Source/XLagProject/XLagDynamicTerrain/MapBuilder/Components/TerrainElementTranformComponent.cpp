#include "TerrainElementTranformComponent.h"

TerrainElementTranformComponent::TerrainElementTranformComponent(const ITerrainElementTransofmCondition& condition, const TerrainElementEnum fromElement, const TerrainElementEnum toElement)
	:_condition(condition), _fromElement(fromElement), _toElement(toElement)
{
	
}

void TerrainElementTranformComponent::DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy)
{
	if (!IsCondition(accessor, ix, iy))
		return;

	accessor->Point(ix, iy).ChangeTopKind(_toElement);
}

bool TerrainElementTranformComponent::IsCondition(ITerrainMapAccessor *const accessor, const int& ix, const int& iy)
{
	return (_fromElement == -1 || accessor->Point(ix, iy).GetTopKind() ==  _fromElement)
		&& _condition.IsCondition(accessor, ix, iy);
}