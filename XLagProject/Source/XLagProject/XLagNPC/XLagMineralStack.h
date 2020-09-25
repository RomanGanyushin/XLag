#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "../XLagMinerals/Models/XLagMineralDesc.h"
#include "XLagMineralStack.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagMineralStack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXLagMineralStack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(const FXLagMineralDesc& mineral);
	void AddMineral(float quantity);

	UPROPERTY(VisibleAnywhere, Category = "Mineral Stack Properties")
	FXLagMineralDesc ContentMineral;
	
	// Количество материала
	UPROPERTY(VisibleAnywhere, Category = "Current State Properties")
	float MineralQuantity = 0;

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* MineralStack;

private:
	void CreateView();
};
