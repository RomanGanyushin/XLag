#pragma once
#include "XLagNPCTaskBase.h"

class XLagNPCTaskRepeat : public XLagNPCTaskBase
{
public:

	XLagNPCTaskRepeat(std::function<bool()> where_if)
	{
		Where_if = where_if;
	}
	
	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		if (Where_if())
		{
			context->Repeat();
		}	
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override
	{
		return true;
	}

	bool IsNpcRequire() override { return false; }
	bool IsAwait() override { return true; }

private:
	std::function<bool()> Where_if;
};