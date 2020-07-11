// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XLagCuttableTreeBase.h"
#include "XLagTimberStack.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagTimberStack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXLagTimberStack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void AddTimber(AXLagCuttableTreeBase* tree);

	UPROPERTY(VisibleAnywhere, Category = "Current State Properties")
	// Количество деревьев в стопке.
	int Count = 0;

private:
	FVector CalculatePosition(int num, float diameter);
	inline float DeltaHeigth(float diameter) { return sqrt(pow(diameter, 2) - pow(diameter / 2.f, 2)); }
};
