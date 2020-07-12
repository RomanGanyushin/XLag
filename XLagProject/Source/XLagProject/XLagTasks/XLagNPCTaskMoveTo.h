#pragma once
#include "XLagNPCTaskBase.h"

class XLagNPCTaskMoveTo : public XLagNPCTaskBase
{
public:
	XLagNPCTaskMoveTo(const FVector& locator, float sufficientDistance, float deadlineTime = 1e10f)
		:TargetLocation(locator), SufficientDistance(sufficientDistance), DeadlineTime(deadlineTime)
	{
		#ifdef ENABLE_TASK_LOG
		UE_LOG(LogTemp, Log, TEXT("Create task: MoveTo (%f,%f,%f)"), locator.X, locator.Y, locator.Z);
		#endif
	}

	virtual void Execute(ACharacter *npc, float DeltaTime) override
	{
		auto npcLocation = npc->GetActorLocation();
		auto toMove = TargetLocation - npcLocation; toMove.Z = 0;
		auto dist = toMove.Size();
		if (dist <= SufficientDistance)
		{
			#ifdef ENABLE_TASK_LOG
				UE_LOG(LogTemp, Log, TEXT("Task: MoveTo Complite"));
			#endif

			Completed = true;
			return;
		}

		wayTime += DeltaTime;
		if (wayTime >= DeadlineTime)
		{
			npc->SetActorLocation(TargetLocation);
		}

		toMove.Normalize();

		npc->AddMovementInput(toMove, DeltaTime * 10);
		auto rotator = toMove.Rotation();
		rotator.Pitch = 0; // 0 off the pitch 

		auto delta = rotator - npc->GetActorRotation();
		delta.Pitch = 0;
		npc->AddActorLocalRotation(delta);

		#ifdef ENABLE_TASK_LOG
		UE_LOG(LogTemp, Log, TEXT("Task: MoveTo (%f,%f,%f). Distance: %f(%f), Way Time: %f(%f)"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z,
			dist, SufficientDistance, wayTime, DeadlineTime);
		#endif
	}

	virtual bool IsSuccess() override { return Completed; }

	const FVector TargetLocation;
	const float SufficientDistance;
	float wayTime = 0.f;
	const float DeadlineTime;
	bool Completed = false;
};
