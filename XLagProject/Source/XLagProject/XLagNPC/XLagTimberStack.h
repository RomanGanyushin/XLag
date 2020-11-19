// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "XLagSwapableObject.h"
#include "XLagTimberStack.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagTimberStack : public AXLagSwapableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXLagTimberStack();
	virtual void AssignObject(const FXLagDynamicObject& object) override;

	// Количество деревьев в стопке.
	UPROPERTY(VisibleAnywhere, Category = "Current State Properties")
		int Count = 0;

	UStaticMesh* Tepmplate;

private:
	UFUNCTION()
	void OnPropertyChanged(uint8 id, const FXLagObjectProperties& properties);

	void UpdateView(int newTimberCount);
	FVector CalculatePosition(int num, float diameter);
	inline float DeltaHeigth(float diameter) { return sqrt(pow(diameter, 2) - pow(diameter / 2.f, 2)); }

	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetTimberAsset()
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/HillTree_02/HillTree_02_Timber"));
		return &Asset;
	}
};
