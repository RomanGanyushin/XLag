#pragma once
#include "ProceduralMeshComponent.h"
#include "XLagNPCBase.h"
#include "XLagSwapableObject.h"
#include "XLagLooseStackBase.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagLooseStackBase : public AXLagSwapableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXLagLooseStackBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CreateView();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Stack Properties")
		int SizeX;

	UPROPERTY(VisibleAnywhere, Category = "Stack Properties")
		int SizeY;

	// Количество материала
	UPROPERTY(VisibleAnywhere, Category = "Current State Properties")
		float StackQuantity = 0;

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* ThisStack;

	void AssignObject(const FXLagDynamicObject& object) override;

protected:
	UFUNCTION()
	void OnPropertyChanged(uint8 id, const FXLagObjectProperties& properties);
};
