#pragma once
#include "../ITerrainMapEditComponent.h"
#include "../../../Common/TerrainElementEnum.h"
#include "PerlinFillerMapEditSettings.h"
#include "Perlin2DAlgorithm.hpp"

// Компонент для заполнения карты по шуму Перлина.
class PerlinFillerMapEditComponent : public ITerrainMapEditComponent
{
public:
	// Инициализует новый экземпляр класса.
	PerlinFillerMapEditComponent(const TerrainElementEnum element, const PerlinFillerMapEditSettings settings = PerlinFillerMapEditSettings());

	// Освобождает ресурсы экземпляра класса.
	~PerlinFillerMapEditComponent() override;

	// #inhereddoc
	void DoEdit(ITerrainMapAccessor *const accessor, const int& ix, const int& iy) override;

private:
	// Реализация алгоритма шума Перлина.
	Perlin2DAlgorithm *_perlin2DAlgorithm = nullptr;

	// Элемент земли которым заполняется карта.
	const TerrainElementEnum _element;
	const PerlinFillerMapEditSettings _settings;
};