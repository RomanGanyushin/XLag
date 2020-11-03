#pragma once
#include <map>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "XLagNPCBase.h"
#include "XLagProductStack.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagProductStack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXLagProductStack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void AddQuantity(float quantity);

	UPROPERTY(VisibleAnywhere, Category = "Stack Properties")
		int SizeX;

	UPROPERTY(VisibleAnywhere, Category = "Stack Properties")
		int SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack Properties")
	UStaticMesh* ProductPresentMesh;

	// Количество материала
	UPROPERTY(VisibleAnywhere, Category = "Current State Properties")
		float StackQuantity = 0;

private:
	void CreateView();
	void ResetView();
	void CreateOddLayer(float offset_z, int& counter);
	void CreateEvenLayer(float offset_z, int& counter);
	TArray<UStaticMeshComponent*> _elements;
};
