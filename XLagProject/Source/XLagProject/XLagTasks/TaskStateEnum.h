#pragma once

UENUM(BlueprintType)
enum TaskStateEnum
{
	Created UMETA(DisplayName = "Created"),
	Recruitment UMETA(DisplayName = "Recruitment"),
	InProgess UMETA(DisplayName = "InProgess"),
	Done UMETA(DisplayName = "Done")
};