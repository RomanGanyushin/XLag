#pragma once
#include "Models/XLagMineralDesc.h"
#include "XLagMineralManager.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagMineralManager : public AActor
{
	GENERATED_BODY()

public:
	AXLagMineralManager();

	// Коллекция полезных ископаемых.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Descriptions") 
		TArray<FXLagMineralDesc> MineralDescCollection;

	// Метод завершения создания коллекции.
	UFUNCTION(BlueprintCallable) void CompliteCreate();

	// Получает коллецию изыскиваемых полезных ископаемых.
	UFUNCTION(BlueprintCallable) const TArray<FXLagMineralDesc> GetSearchableMeneralDescCollection() const;

public:
	static AXLagMineralManager* GetMineralManager()
	{
		for (TObjectIterator<AXLagMineralManager> It; It; ++It)
		{
			AXLagMineralManager* CurrentObject = (AXLagMineralManager*)*It;
			return (AXLagMineralManager *)CurrentObject;
		}

		return nullptr;
	}
};