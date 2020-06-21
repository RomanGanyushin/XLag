#pragma once
#include "../ITerrainMapEditComponent.h"
#include "../TerrainElementEnum.h"
#include "ITerrainElementTransofmCondition.h"

class TerrainElementTranformComponent : public ITerrainMapEditComponent
{
public:
	// »нициализует новый экземпл€р класса.
	TerrainElementTranformComponent(const ITerrainElementTransofmCondition& condition, const TerrainElementEnum fromElement, const TerrainElementEnum toElement);

	// #inhereddoc
	void DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy) override;

private:
	inline bool IsCondition(ITerrainMapAccessor *const accessor, const int& ix, const int& iy);

private:
	const ITerrainElementTransofmCondition& _condition;
	const TerrainElementEnum _fromElement;
	const TerrainElementEnum _toElement;
};
