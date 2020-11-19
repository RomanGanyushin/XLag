#pragma once
#include "../../XLagNPC/XLagNPCBase.h"
#include "../../XLagDynamicTerrain/XLagDynamicTerrainMapAccessor.h"
#include "../../XLagDynamicTerrainBase.h"
#include "XLagNPCMovementTaskBase.h"

class XLagNPCTaskMoveToFind : public XLagNPCMovementTaskBase
{
public: 
	XLagNPCTaskMoveToFind(float sufficientDistance, float deadlineTime = 1e10f)
		:XLagNPCMovementTaskBase(sufficientDistance, deadlineTime)
	{
		_targetLocation = FVector::ZeroVector;
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (IsSufficientDistance(npc))
		{
			Completed = true;
			return;
		}

		if (_targetLocation == FVector::ZeroVector)
		{
			auto pers = dynamic_cast<AXLagNPCBase*>(npc);
			if (pers->FindCellIndex == -1)
				return;

			auto terrain = AXLagDynamicTerrainBase::GetDynamicTerrainBase();		
			_targetLocation = terrain->Map->GetWorldPosition(pers->FindCellIndex, GetPositionEnum::CenterHeghtPosition);
		}

		DoMove(DeltaTime, npc);
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }
};
