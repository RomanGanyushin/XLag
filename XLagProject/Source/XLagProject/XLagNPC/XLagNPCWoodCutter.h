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
	void DoCutTree(AXLagCuttableTreeBase *TargetTree);

	// Обтесывай дерево.
	void DoBroachTree(AXLagCuttableTreeBase *TargetTree);
};
