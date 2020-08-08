// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "XLagCuttableTreeBase.h"
#include "XLagNPCWoodCutter.generated.h"

/**
 * 
 */
UCLASS()
class XLAGPROJECT_API AXLagNPCWoodCutter : public AXLagNPCBase
{
	GENERATED_BODY()
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Руби дерево.
	void BeginCutTree(AXLagCuttableTreeBase *targetTree);

	// Обтесывай дерево.
	void BeginBroachTree(AXLagCuttableTreeBase *targetTree);

	// Отменяет выполняемую команду.
	void Cancel();


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Woodcutter Cutting")
	bool  IsCutting = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Woodcutter Cutting")
	bool  IsBroaching = false;

private:
	AXLagCuttableTreeBase *TargetTree = nullptr;
};
