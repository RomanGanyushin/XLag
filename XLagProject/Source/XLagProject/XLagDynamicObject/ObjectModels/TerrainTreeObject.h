#pragma once
#include "TerrainObjectBase.h"

UENUM()
enum TreeParameterId
{
	ParId_TreeKind = CommonParameterId::ParId_UserDefined + 0,
	ParId_TreeAge = CommonParameterId::ParId_UserDefined + 2,
	ParId_TreeState = CommonParameterId::ParId_UserDefined + 3,
	ParId_TreeSustainability = CommonParameterId::ParId_UserDefined + 4
};

enum TreeState
{
	Growing_,
	Falling_,
	Fallen_,
	Timber_
};

struct TerrainTreeObject : public TerrainObjectBase
{
	TerrainTreeObject(FXLagObjectProperties& properties) : TerrainObjectBase(properties)
	{
	}

	void SetAge(const int8 age)
	{
		Properties.SetValue(ParId_TreeAge, age);
	}

	const int8 GetAge()
	{
		return Properties.GetValue<int8>(ParId_TreeAge);
	}

	void SetKind(const int8 type)
	{
		Properties.SetValue(ParId_TreeAge, type);
	}

	const int8 GetKind()
	{
		return Properties.GetValue<int8>(ParId_TreeKind);
	}

	void SetTreeState(const TreeState state)
	{
		Properties.SetValue(ParId_TreeState, (int8)state);
	}

	const TreeState GetTreeState()
	{
		return (TreeState)Properties.GetValue<int8>(ParId_TreeState);
	}

};