#include "XLagBuildingDescription.h"

void FXLagBuildingDescription::SetGeneralPlain(FGeneralPlain& generalPlain)
{
	_generalPlain = generalPlain;
	IsExist = true;
}

const FGeneralPlain& FXLagBuildingDescription::GetGeneralPlain() const
{
	return _generalPlain;
}