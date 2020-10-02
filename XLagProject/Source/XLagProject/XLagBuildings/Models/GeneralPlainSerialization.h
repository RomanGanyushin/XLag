#pragma once

#include "GeneralPlain.h"

class UGeneralPlainSerialization
{
public:
	static FGeneralPlain* LoadFromFile(FString filename);
	static TArray<FString> ScanFiles();
};
