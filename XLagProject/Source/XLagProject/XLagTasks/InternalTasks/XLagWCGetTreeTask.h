#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "../../XLagNPC/XLagCuttableTreeBase.h"
#include "../../XLagNPC/XLagNPCWoodCutter.h"

/*
«адача дл€ дровосека - вз€ть дерево (бревно).
*/
class XLagWCGetTreeTask : public XLagNPCTaskBase
{
public:
	XLagWCGetTreeTask(AXLagCuttableTreeBase* tree)
		:Tree(tree)
	{

	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		/*if (Completed)
			return;

		auto woodcutter = dynamic_cast<AXLagNPCWoodCutter*>(npc);
		if (woodcutter == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("XLagWCBroachTreeTask::Execute "));
		}

		if (!Tree->IsTimber())
			return;

		auto loc = woodcutter->GetActorLocation();
		auto vec = 200.f * woodcutter->GetActorForwardVector() + FVector(0.f, 50, 80);
		auto dir = woodcutter->GetActorRotation(); dir.Pitch += 90;

		Tree->SetActorLocation(loc + vec);
		Tree->SetActorRotation(dir);

		Tree->SetActorEnableCollision(false);
		Tree->AttachToActor(woodcutter, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));	
		Completed = true;*/
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override { return Completed; }

	AXLagCuttableTreeBase* Tree;
	bool Completed = false;
};
