// Copyright Epic Games, Inc. All Rights Reserved.

#include "XLagProjectGameMode.h"
#include "XLagProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "XLagDynamicTerrainBase.h"
#include "XLagDynamicObject/XLagDynamicObjectsManager.h"
#include "Common/XLagObjectProperties.h"

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
}

void AXLagProjectGameMode::SetTerrainMap(const FXLagDynamicTerrainMap& map, const FXLagDynamicObjects& objects)
{
	TerrainMap = map;
	TerrainObjects = objects;

	if (!TerrainMap.IsCreated)
	{
		TerrainMap.Map.SetNum(TerrainMap.SizeX * TerrainMap.SizeY);
	}

	AXLagDynamicObjectsManager::GetManagment()->OnInitialze(this);
	AXLagDynamicTerrainBase::GetDynamicTerrainBase()->OnInitialze(this);	
}
