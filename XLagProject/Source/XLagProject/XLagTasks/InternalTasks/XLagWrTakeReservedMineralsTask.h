#pragma once
#include "XLagNPCMovementTaskBase.h"
#include "../../XLagNPC/XLagNPCWorker.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagMinerals/XLagMineralManager.h"

class XLagWrTakeReservedMineralsTask : public XLagNPCMovementTaskBase
{
public:
	XLagWrTakeReservedMineralsTask(const float& sufficientDistance, float deadlineTime = 1e10f)
		: XLagNPCMovementTaskBase(sufficientDistance, deadlineTime)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Completed)
			return;

		auto worker = dynamic_cast<AXLagNPCWorker*>(npc);
		if (worker == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("XLagWrMineralWaitTask::Execute npc not Worker"));
			return;
		}

		/*if (currentStack == nullptr)
		{
			auto mineralManager = AXLagMineralManager::GetMineralManager();
			auto stacks = mineralManager->FindReserveredMineralStackFor(worker);
			if (stacks.Num() == 0)
			{
				Completed = true;
				return;
			}

			currentStack = stacks[0];
			_targetLocation = currentStack->GetActorLocation();	
		}

		if (!IsSufficientDistance(npc))
		{
			DoMove(DeltaTime, npc);
			return;
		}*/

		Completed = worker->TakeReservedMineral(currentStack, DeltaTime);
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return Completed;
	}

private:
	AXLagMineralStack* currentStack = nullptr;
};