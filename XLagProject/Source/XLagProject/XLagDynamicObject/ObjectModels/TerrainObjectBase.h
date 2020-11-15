#pragma once
#include "../../Common/XLagObjectProperties.h"

UENUM()
enum CommonParameterId
{
	ParId_Location = 0,
	ParId_Rotation = 1,
	ParId_UserDefined = 2
};

struct TerrainObjectBase
{
	TerrainObjectBase(FXLagObjectProperties& properties)
		: Properties(properties)
	{	
	}

	FXLagObjectProperties& Properties;

	void SetLocation(const FVector& location)
	{
		Properties.SetValue(ParId_Location, location);
	}

	FVector GetLocation() const
	{
		return Properties.GetValue<FVector>(ParId_Location);
	}

	bool HasLocation() const
	{
		return Properties.HasValue(ParId_Location);
	}

	void SetRotation(const FRotator& rotator)
	{
		Properties.SetValue(ParId_Rotation, rotator);
	}

	FRotator GetRotation() const
	{
		return Properties.GetValue<FRotator>(ParId_Rotation);
	}

	bool HasRotation() const
	{
		return Properties.HasValue(ParId_Rotation);
	}
};