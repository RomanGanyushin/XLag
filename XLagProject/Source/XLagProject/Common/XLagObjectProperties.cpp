#include "XLagObjectProperties.h"

FXLagObjectPropertyPackage::FXLagObjectPropertyPackage(const FVariant& value)
{
	Pack(value);
}

void FXLagObjectPropertyPackage::Pack(const FVariant& value)
{
	Data = value.GetBytes();
}

const bool FXLagObjectPropertyPackage::operator==(const FVariant& value) 
{ 
	auto is = value.GetBytes() == Data;
	return value.GetBytes() == Data;
}

bool FXLagObjectProperties::HasValue(uint8 id) const
{
	return Properties.Contains(id);
}

void FXLagObjectProperties::SetValue(uint8 id, const FVariant& value)
{
	if (!Properties.Contains(id))
	{
		Properties.Add(id, FXLagObjectPropertyPackage(value));	
	}
	else
	{
		if (Properties[id] == value)
			return;
		{ 
			Properties[id].Pack(value);
		}		
	}

	PropertyChangedEvent.Broadcast(id);
}

void FXLagObjectProperties::SetProperties(const FXLagObjectProperties& source)
{
	Properties = source.Properties;
}