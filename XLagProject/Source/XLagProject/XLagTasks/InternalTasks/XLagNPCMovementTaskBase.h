#pragma once
#include "XLagNPCTaskBase.h"

class XLagNPCMovementTaskBase : public XLagNPCTaskBase
{
public:
	XLagNPCMovementTaskBase(const float& sufficientDistance, const float& deadlineTime = 1e10f)
		:_sufficientDistance(sufficientDistance), _deadlineTime(deadlineTime)
	{
	}

	bool IsSufficientDistance(ACharacter *npc)
	{
		auto npcLocation = npc->GetActorLocation();
		auto toMove = _targetLocation - npcLocation; toMove.Z = 0;
		auto dist = toMove.Size();
		return dist <= _sufficientDistance;
	}

	void DoMove(float deltaTime, ACharacter *npc)
	{
		_wayTime += deltaTime;
		auto npcLocation = npc->GetActorLocation();
		auto toMove = _targetLocation - npcLocation; toMove.Z = 0;

		if (_wayTime >= _deadlineTime)
		{
			npc->SetActorLocation(_targetLocation);
		}

		toMove.Normalize();

		npc->AddMovementInput(toMove, 10);
		auto rotator = toMove.Rotation();
		rotator.Pitch = 0; // 0 off the pitch 

		auto delta = rotator - npc->GetActorRotation();
		delta.Pitch = 0;
		npc->AddActorLocalRotation(delta);
	}

	void Reset() override
	{
		XLagNPCTaskBase::Reset();
		_wayTime = 0;
	}

protected:
	const float _sufficientDistance;
	const float _deadlineTime;
	FVector _targetLocation;
	float _wayTime = 0.f;
};