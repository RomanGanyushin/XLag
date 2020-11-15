#pragma once
#include "TerrainObjectBehaviorBase.h"
#include "TerrainCropObject.h"

class TerrainCropObjectBehavior : public TerrainObjectBehaviorBase
{
public:
	virtual void OnTick(FXLagDynamicObject* object, float deltaTime) override
	{
		TerrainCropObject cropObject(*object);

		auto lifetime = cropObject.GetLifetime();
		auto deltaEvalution = 100.0f * deltaTime / lifetime;
		auto currentEvalution = cropObject.GetEvalution();
		auto newEvalution = currentEvalution + deltaEvalution;
		
		newEvalution = std::min(newEvalution, 100.0f);
		cropObject.SetEvalution(newEvalution);

		if (currentEvalution != newEvalution && newEvalution == 100.0f)
		{
			cropObject.SetCropQuantity(5.0f);
		}
	}
};