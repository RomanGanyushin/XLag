#pragma once
#include "../XLagProjectGameMode.h"
#include "ObjectModels/TerrainObjectBehaviorBase.h"
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
	FXLagDynamicObjects& GetObjects() { return *_terrainObjects; }

protected:
	UFUNCTION() 
	void OnAddNewObject(const int32 newIndex);

	UFUNCTION()
	void OnRemovingObject(const int32 removingIndex);

	// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;

private:
	FXLagDynamicObjects* _terrainObjects = nullptr;
	FXLagDynamicTerrainMap* _terrainMap = nullptr;
	TMap<XLagDynamicObjectType, std::shared_ptr<TerrainObjectBehaviorBase>> _behaviors;
};