#pragma once

#include "../ITerrainMapEditComponent.h"

class AligmentDigEditComponent : public ITerrainMapEditComponent
{
public:
	// ������������ ����� ��������� ������.
	AligmentDigEditComponent();

	// #inhereddoc
	void DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy) override; 
};