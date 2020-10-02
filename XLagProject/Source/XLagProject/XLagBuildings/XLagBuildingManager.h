#pragma once

#include "XLagBuildingDescription.h"
#include "XLagBuilding.h"
#include "../Common/ITerrainMapAccessor.h"
#include "../XLagGeometry/GeometryPrimitives.h"
#include "XLagBuildingManager.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagBuildingManager : public AActor
{
	GENERATED_BODY()
public:
	AXLagBuildingManager();

	inline static AXLagBuildingManager* GetManagment()
	{
		AXLagBuildingManager *currentObject = nullptr;

		for (TObjectIterator<AXLagBuildingManager> It; It; ++It)
		{
			currentObject = *It;
		}

		return currentObject;
	}

	void SetMapAccessor(std::shared_ptr<ITerrainMapAccessor> accessor) { MapAccessor = accessor; }
	
	// Коллекция построек.
	UPROPERTY(BlueprintReadOnly) TArray<FXLagBuildingDescription> BuildingCollection;

	// Текущее выбранное сооружение.
	UPROPERTY(BlueprintGetter = GetSelectBuilding, BlueprintSetter = SetSelectBuilding)
		FXLagBuildingDescription SelectBuilding;

	// Текущее выбранное сооружение.
	UPROPERTY(BlueprintGetter = GetPreviewSelectBuilding, BlueprintSetter = SetPreviewSelectBuilding)
		bool PreviewSelectBuilding;

	// Получает значение, показывающее что сооружение выбрано.
	UPROPERTY(BlueprintReadOnly)
		bool IsSelectBuilding;

	UFUNCTION(BlueprintCallable)
		const FXLagBuildingDescription& GetSelectBuilding() const;

	UFUNCTION(BlueprintCallable)
		void SetSelectBuilding(FXLagBuildingDescription select);

	UFUNCTION(BlueprintCallable)
		bool GetPreviewSelectBuilding() const;

	UFUNCTION(BlueprintCallable)
		void SetPreviewSelectBuilding(const bool preview);

	UFUNCTION(BlueprintCallable)
		void SetPreviewPosition(const float x, const float y);

	UFUNCTION(BlueprintCallable)
		AXLagBuilding *BuildingSiteFound(const FXLagBuildingDescription& building);

private:
	FXLagBuildingDescription _selectBuilding;
	AXLagBuilding *_previewBuilding;
	bool _isPreviewSelectBuilding;
	std::shared_ptr<ITerrainMapAccessor> MapAccessor;

private:
	void CreateBuildingCollection();
	void CreatePreviewSelectBuilding();
	void DestroyPreviewSelectBuilding();
};