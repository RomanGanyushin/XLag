#pragma once
#include "TerrainObjectBehaviorBase.h"
#include "TerrainTreeObject.h"

class TerrainTreeObjectBehavior : public TerrainObjectBehaviorBase
{
public:
	virtual void OnTick(FXLagDynamicObject* object, float deltaTime) override
	{
		TerrainTreeObject treeObject(*object);

		auto state = treeObject.GetTreeState();
		auto sustainability = treeObject.GetTreeSustainability();
		auto broach = treeObject.GetTreeBroach();

		if (state == TreeState::Growing && sustainability == 0.0f)
		{
			treeObject.SetTreeState(TreeState::Falling);
			treeObject.SetLocation(treeObject.GetLocation() + FVector(0, 0, 25));
		}
		else if (state == TreeState::Falling)
		{
			auto rotator = treeObject.GetRotation();
			rotator += FRotator(0.25f, 0, 0);
			treeObject.SetRotation(rotator);

			if (rotator.Pitch > 85)
			{
				treeObject.SetTreeState(TreeState::Fallen);
			}
		}
		else if (state == TreeState::Fallen)
		{
			if (broach >= 5)
			{
				treeObject.SetTreeState(TreeState::Timber);
			}		
		}
	}
};