#include "TerrainElementTranformComponent.h"
#include "../../XLagDynamicTerrainMapItemOperation.h"

TerrainElementTranformComponent::TerrainElementTranformComponent(const ITerrainElementTransofmCondition& condition, const TerrainElementEnum fromElement, const TerrainElementEnum toElement)
	:_condition(condition), _fromElement(fromElement), _toElement(toElement)
{
	
}

void TerrainElementTranformComponent::DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy)
{
	if (accessor == nullptr)
	{
		return;
	}

	if (!IsCondition(accessor, ix, iy))
		return;

	XLagDynamicTerrainMapItemOperation(accessor->Point(ix, iy)).ChangeTopKind(_toElement);
}

bool TerrainElementTranformComponent::IsCondition(ITerrainMapAccessor *const accessor, const int& ix, const int& iy)
{
	if (accessor == nullptr)
	{
		return false;
	}

	return (_fromElement == -1 || XLagDynamicTerrainMapItemOperation(accessor->Point(ix, iy)).GetTopKind() ==  _fromElement)
		&& _condition.IsCondition(accessor, ix, iy);
}