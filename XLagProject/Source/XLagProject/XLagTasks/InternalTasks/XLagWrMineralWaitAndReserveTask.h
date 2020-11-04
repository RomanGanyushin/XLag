#pragma once
#include "XLagNPCTaskBase.h"
#include "../../XLagNPC/XLagNPCWorker.h"
#include "../../Common/ITerrainMapAccessor.h"
#include "../../XLagMinerals/XLagMineralManager.h"

class XLagWrMineralWaitAndReserveTask : public XLagNPCTaskBase
{
public:
	XLagWrMineralWaitAndReserveTask(std::string mineralName, float quanity)
		:_mineralName(mineralName), _quanity(quanity)
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

		if (worker->Bag.Has(FString(_mineralName.c_str()), _quanity))
		{
			Completed = true;
			return;
		}

		// TODO: Перенести в рабочего
		auto mineralManager = AXLagMineralManager::GetMineralManager();
		auto stacks = mineralManager->FindMineralStackFor(FString(_mineralName.c_str()));

		for (auto& it : stacks)
		{
			auto avaible = it->GetAvaibleQuantity();
			if (avaible > _quanity)
			{
				it->Reserve(worker, _quanity);
				Completed = true;
				break;
			}
		}	
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return Completed;
	}

private:
	const std::string _mineralName;
	const float _quanity;
};