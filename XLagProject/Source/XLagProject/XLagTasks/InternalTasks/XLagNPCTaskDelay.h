#pragma once
#include "XLagNPCTaskBase.h"

class XLagNPCTaskDelay : public XLagNPCTaskBase
{
public:
	XLagNPCTaskDelay(float delay)
		:Delay(delay)
	{
	}

	virtual void Execute(ACharacter *npc, XLagNPCTaskContext* context, float DeltaTime, int subLevel) override
	{
		TimeCounter += DeltaTime;
	}

	virtual bool IsSuccess(XLagNPCTaskContext* context, int subLevel) override 
	{ 
		auto isSuccess = TimeCounter >= Delay;
		return isSuccess;
	}

	bool IsNpcRequire() override { return false; }

	bool IsAwait() override { return true; }
private:
	float Delay = 0.0f;
	float TimeCounter = 0.0f;
};