#include "TerrainMapEditEditor.h"

TerrainMapEditEditor::TerrainMapEditEditor(ITerrainMapAccessor *const accessor)
	:_accessor(accessor)
{
}

void TerrainMapEditEditor::FillByXY(ITerrainMapEditComponent *component)
{
	const int size_x = _accessor->SizeX();
	const int size_y = _accessor->SizeY();

	component->PrepareForEdit(_accessor);

	for (auto index_x = 0; index_x < size_x; index_x++)
	{
		for (auto index_y = 0; index_y < size_y; index_y++)
		{
			component->DoEdit(_accessor, index_x, index_y);
		}
	}
}