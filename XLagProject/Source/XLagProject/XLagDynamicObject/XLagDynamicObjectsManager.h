#pragma once
#include "../XLagProjectGameMode.h"
#include "XLagDynamicObjectsManager.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagDynamicObjectsManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXLagDynamicObjectsManager();

	inline static AXLagDynamicObjectsManager* GetManagment()
	{
		AXLagDynamicObjectsManager *currentObject = nullptr;

		for (TObjectIterator<AXLagDynamicObjectsManager> It; It; ++It)
		{
			currentObject = *It;
		}

		return currentObject;
	}

public:
	UFUNCTION()
	void OnInitialze(AGameModeBase* gameMode);
	
	UFUNCTION() 
	void OnAddNewObject(const FXLagDynamicObject& object);
};