// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "XLagNPCBase.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"
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
	bool CutTree(FXLagDynamicTerrainMapItem& cell, float DeltaTime);

	// Обтесывай дерево.
	bool BroachTree(FXLagDynamicTerrainMapItem& cell, float DeltaTime);

	// Возьми дерево.
	bool GetTree(FXLagDynamicTerrainMapItem& cell, float DeltaTime);

	// Найди стопку.
	bool SearchStack();

	// Положи дерево в стопку.
	bool PutTreeToStack(float DeltaTime);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Woodcutter Cutting")
	bool  IsCutting = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Woodcutter Cutting")
	bool  IsBroaching = false;

	virtual void OfferAccept(UXLagTaskBase* task) override;

protected:
	virtual ProfessionTypeEnum GetCurrentProfession() override { return ProfessionTypeEnum::Treecutter; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) override { return true; }
};
