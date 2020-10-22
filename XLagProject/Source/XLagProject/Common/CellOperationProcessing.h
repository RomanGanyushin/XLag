#pragma once
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "CellOperationEnum.h"

class CellOperationProcessing
{
public:
	CellOperationProcessing(XLagDynamicTerrainMapItem* cell, CellOperationEnum operation)
		:Cell(cell), Operation(operation)
	{
		if (cell->OperationTimeMap.find(operation) == cell->OperationTimeMap.end())
		{
			cell->OperationTimeMap[operation] = 0.0f;
		}
	}

	const bool IsComplete()
	{
		return Cell->OperationTimeMap[Operation] >= 100.0f;
	}

	const bool IsCompleting()
	{
		return _completing;
	}

	const bool IsEmpty()
	{
		return Cell->OperationTimeMap[Operation] <= 0.0f;
	}

	const float Increase(float value)
	{
		if (IsComplete())
			return 0.0f;

		auto oldValue = Cell->OperationTimeMap[Operation];
		Cell->OperationTimeMap[Operation] = std::max(Cell->OperationTimeMap[Operation] + value , 100.0f);

		_completing = Cell->OperationTimeMap[Operation] == 100.0f;
		return Cell->OperationTimeMap[Operation] - oldValue;
	}

	const float Decrease(float value)
	{
		auto oldValue = Cell->OperationTimeMap[Operation];
		Cell->OperationTimeMap[Operation] = std::min(Cell->OperationTimeMap[Operation] - value, 0.0f);
		return oldValue - Cell->OperationTimeMap[Operation];
	}

	void Set(float value)
	{
		Cell->OperationTimeMap[Operation] = value;
	}

	float Get()
	{
		return Cell->OperationTimeMap[Operation];
	}

private:
	XLagDynamicTerrainMapItem* Cell;
	CellOperationEnum Operation;
	bool _completing = false;
};