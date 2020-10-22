#pragma once

UENUM(BlueprintType)
enum TaskStateEnum
{
	Created UMETA(DisplayName = "Created"),
	Recruitment UMETA(DisplayName = "Recruitment"),
	InProgess UMETA(DisplayName = "InProgess"),
	Waiting UMETA(DisplayName = "Waiting"),
	Done UMETA(DisplayName = "Done")
};