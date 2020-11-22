#pragma once
#include "XLagLooseStackBase.h"
#include "../XLagProduction/XLagProductionSchemasManager.h"
#include "XLagProductStack.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagProductStack : public AXLagLooseStackBase
{
	GENERATED_BODY()

public:
	void Initialize(const FXLagProductionSchema& product, const int sizeX, const int sizeY);
protected:
	virtual void CreateView() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack Properties")
	UStaticMesh* ProductPresentMesh;

private:
	void ResetView();
	void CreateOddLayer(float offset_z, int& counter);
	void CreateEvenLayer(float offset_z, int& counter);
	TArray<UStaticMeshComponent*> _elements;

	FXLagProductionSchema ContentProduct;
};
