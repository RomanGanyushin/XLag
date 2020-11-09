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
		//DefaultPawnClass = PlayerPawnBPClass.Class;
		DefaultPawnClass = nullptr;
		
	}
	// устанавливаем контроллер персонажа
	static ConstructorHelpers::FClassFinder<APlayerController> ThirdPersonController(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonController"));
	if (ThirdPersonController.Class != NULL)
	{
		PlayerControllerClass = ThirdPersonController.Class;
	}

	///
	TerrainMap.Map.SetNum(100 * 100);
	TerrainMap.Scale = 100.0f;
	TerrainMap.SizeX = 100;
	TerrainMap.SizeY = 100;
}
