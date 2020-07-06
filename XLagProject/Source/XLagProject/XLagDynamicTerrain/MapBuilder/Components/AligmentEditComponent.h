#pragma once

#include "../ITerrainMapEditComponent.h"
#include "AligmentEditComponentSettings.h"

class AligmentEditComponent : public ITerrainMapEditComponent
{
public:
	// »нициализует новый экземпл€р класса.
	AligmentEditComponent(const AligmentEditComponentSettings& settings);

	// #inhereddoc
	void DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy) override; 

	// #inhereddoc
	void PrepareForEdit(ITerrainMapAccessor *const accessor) override;

private:
	const AligmentEditComponentSettings& _settings;
	float _level = 0.f;
};