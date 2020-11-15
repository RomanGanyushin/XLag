#pragma once
#include "Models/XLagCropDescription.h"
#include "XLagCropManager.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagCropManager : public AActor
{
	GENERATED_BODY()

public:
	AXLagCropManager();

	// Коллекция полезных ископаемых.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Descriptions")
		TArray<FXLagCropDescription> CropDescCollection;

	// Метод завершения создания коллекции.
	UFUNCTION(BlueprintCallable) void CompliteCreate();
	UFUNCTION(BlueprintCallable) const bool Empty() const;

	UFUNCTION(BlueprintCallable) const FXLagCropDescription FindById(const int id) const;

public:
	static AXLagCropManager* GetCropsManager()
	{
		for (TObjectIterator<AXLagCropManager> It; It; ++It)
		{
			AXLagCropManager* CurrentObject = (AXLagCropManager*)*It;
			return (AXLagCropManager *)CurrentObject;
		}

		return nullptr;
	}
};