#pragma once

#include "../ITerrainMapEditComponent.h"

class AligmentDigEditComponent : public ITerrainMapEditComponent
{
public:
	// »нициализует новый экземпл€р класса.
	AligmentDigEditComponent();

	// #inhereddoc
	void DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy) override; 
};