#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "XLagLooseStackBase.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagLooseStackBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXLagLooseStackBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddQuantity(float quantity);

	UPROPERTY(VisibleAnywhere, Category = "Stack Properties")
		int SizeX;

	UPROPERTY(VisibleAnywhere, Category = "Stack Properties")
		int SizeY;

	// Количество материала
	UPROPERTY(VisibleAnywhere, Category = "Current State Properties")
		float StackQuantity = 0;


	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* ThisStack;

private:
	void CreateView();
};
