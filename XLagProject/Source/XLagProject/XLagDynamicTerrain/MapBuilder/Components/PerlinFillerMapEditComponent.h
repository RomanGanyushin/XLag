#pragma once
#include "../ITerrainMapEditComponent.h"
#include "../../../Common/TerrainElementEnum.h"
#include "../../../XLagGeometry/Algorithms/Perlin2DAlgorithm.hpp"
#include "PerlinFillerMapEditSettings.h"

// ��������� ��� ���������� ����� �� ���� �������.
class PerlinFillerMapEditComponent : public ITerrainMapEditComponent
{
public:
	// ������������ ����� ��������� ������.
	PerlinFillerMapEditComponent(const TerrainElementEnum element, const PerlinFillerMapEditSettings settings = PerlinFillerMapEditSettings());

	// ����������� ������� ���������� ������.
	~PerlinFillerMapEditComponent() override;

	// #inhereddoc
	void DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy) override;

private:
	// ���������� ��������� ���� �������.
	Perlin2DAlgorithm *_perlin2DAlgorithm = nullptr;

	// ������� ����� ������� ����������� �����.
	const TerrainElementEnum _element;
	const PerlinFillerMapEditSettings _settings;
};