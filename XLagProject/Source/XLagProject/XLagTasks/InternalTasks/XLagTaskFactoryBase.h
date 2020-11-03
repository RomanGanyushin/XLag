#pragma once
#include <functional>
#include "XLagNPCTaskMoveTo.h"
#include "XLagNPCTaskDelay.h"
#include "XLagNPCTaskRepeat.h"

bool always_true() { return true; }

class XLagTaskFactoryBase
{
public:
	float CellCompliteDistance = 1.0f;
	float SpaceScale = 100.f;
	float WorldCompliteDistance = CellCompliteDistance * SpaceScale;
	float MovingDeadline = 10.0;

public:

	// Двигайся до указанной локации.
	std::shared_ptr<XLagNPCTaskBase> MoveTo(const FVector& location)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskMoveTo(location, WorldCompliteDistance, MovingDeadline));
	}

	// Пауза.
	std::shared_ptr<XLagNPCTaskBase> Delay(const float& delay)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskDelay(delay));
	}

	std::shared_ptr<XLagNPCTaskBase> Repeat(std::function<bool()> where_if = always_true)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskRepeat(where_if));
	}

};