// Copyright Epic Games, Inc. All Rights Reserved.

#include "XLagProjectGameMode.h"
#include "XLagProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AXLagProjectGameMode::AXLagProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
