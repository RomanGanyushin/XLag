#pragma once
#include "XLagNPCMovementTaskBase.h"

class XLagNPCTaskMoveTo : public XLagNPCMovementTaskBase
{
public:
	XLagNPCTaskMoveTo(const FVector& locator, float sufficientDistance, float deadlineTime = 1e10f)
		:XLagNPCMovementTaskBase(sufficientDistance, deadlineTime)
	{		
		_targetLocation = locator;
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (IsSufficientDistance(npc))
		{
			Completed = true;
			return;
		}

		DoMove(DeltaTime, npc);
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
};
