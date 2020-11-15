#pragma once
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItem.h"
#include "CellOperationEnum.h"

class CellOperationProcessing
{
public:
	CellOperationProcessing(FXLagDynamicTerrainMapItem* cell, CellOperationEnum operation, float completeValue = 100.0f)
		:Cell(cell), Operation(operation), _completeValue(completeValue)
	{
		if (!cell->OperationTimeMap.Contains(operation))
		{
			cell->OperationTimeMap.Add(operation, 0.0f);
		}
	}

	const bool IsComplete()
	{
		return Cell->OperationTimeMap[Operation] >= _completeValue;
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
		Cell->OperationTimeMap[Operation] = std::min(Cell->OperationTimeMap[Operation] + value , _completeValue);

		_completing = Cell->OperationTimeMap[Operation] == _completeValue;
		return Cell->OperationTimeMap[Operation] - oldValue;
	}

	const float Decrease(float value)
	{
		auto oldValue = Cell->OperationTimeMap[Operation];
		Cell->OperationTimeMap[Operation] = std::max(Cell->OperationTimeMap[Operation] - value, 0.0f);
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

	void Reset()
	{
		Set(0.0f);
	}

	void Delete()
	{
		Cell->OperationTimeMap.Remove(Operation);
	}

private:
	FXLagDynamicTerrainMapItem* Cell;
	CellOperationEnum Operation;
	bool _completing = false;
	float _completeValue;
};