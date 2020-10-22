#pragma once
#include "XLagNPCTaskMoveTo.h"
#include "XLagNPCTaskDelay.h"

class XLagTaskFactoryBase
{
public:
	float CompliteDistanceToTree = 1.0f;
	float SpaceScale = 100.f;

public:

	// �������� �� ��������� �������.
	std::shared_ptr<XLagNPCTaskBase> MoveTo(const FVector& location)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskMoveTo(location, CompliteDistanceToTree * SpaceScale, 10));		
	}

	// �����.
	std::shared_ptr<XLagNPCTaskBase> Delay(const float& delay)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskDelay(delay));
	}
};