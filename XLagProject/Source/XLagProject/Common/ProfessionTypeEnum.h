#pragma once
#include "ProfessionTypeEnum.generated.h"

UENUM(BlueprintType)
enum ProfessionTypeEnum
{
	Unknow UMETA(DisplayName = "Unknow"),
	Builder UMETA(DisplayName = "Builder"),
	Miner UMETA(DisplayName = "Miner"),
	Treecutter UMETA(DisplayName = "Treecutter"),
	Farmer UMETA(DisplayName = "Farmer"),
	Worker UMETA(DisplayName = "Worker")
};
