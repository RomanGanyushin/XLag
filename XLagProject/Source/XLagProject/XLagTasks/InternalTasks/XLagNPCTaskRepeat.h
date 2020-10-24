#pragma once
#include "XLagNPCTaskBase.h"

class XLagNPCTaskRepeat : public XLagNPCTaskBase
{
public:

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		context->Repeat();
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return true;
	}

	bool IsNpcRequire() override { return false; }
	bool IsAwait() override { return true; }
};