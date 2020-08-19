#pragma once

#include "GeneralPlain.h"

class UGeneralPlainSerialization
{
public:
	static TSharedPtr<FGeneralPlain> LoadFromFile(FString filename);
};
