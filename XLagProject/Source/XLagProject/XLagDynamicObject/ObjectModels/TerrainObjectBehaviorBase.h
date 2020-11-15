#pragma once

class TerrainObjectBehaviorBase
{
public:
	virtual ~TerrainObjectBehaviorBase() = default;
	virtual void OnTick(FXLagDynamicObject* object, float deltaTime) {};
};