#pragma once
#include "Models/XLagMineralDesc.h"
#include "../XLagNPC/XLagMineralStack.h"
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
	UFUNCTION(BlueprintCallable) const TArray<FXLagMineralDesc> GetSearchableMineralDescCollection() const;

	// Получает коллецию полезных искомпаемых - элементов ландшафта.
	UFUNCTION(BlueprintCallable) const TArray<FXLagMineralDesc> GetTerrainMineralDescCollection() const;

	UFUNCTION(BlueprintCallable) const bool Empty() const;

	UFUNCTION(BlueprintCallable) const FXLagMineralDesc& FindById(const int id) const;

	UFUNCTION(BlueprintCallable) const FXLagMineralDesc& FindByName(const FString& name) const;

	const bool IsNameOfMineral(const FString& name) const;

	const FXLagMineralDesc* SearchByName(const FString& name) const;

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