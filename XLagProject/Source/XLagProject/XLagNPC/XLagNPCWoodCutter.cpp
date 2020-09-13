// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagNPCWoodCutter.h"

void AXLagNPCWoodCutter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetTree == nullptr)
		return;

	if (IsCutting)
	{
		TargetTree->Cut(1);
	}

	if (IsBroaching)
	{
		TargetTree->Broach(1);
	}
}

void AXLagNPCWoodCutter::BeginCutTree(AXLagCuttableTreeBase *targetTree)
{
	UE_LOG(LogTemp, Log, TEXT("Woodcutter cut the tree"));
	
	TargetTree = targetTree;
	IsCutting = true;
	IsBroaching = false;
}

void AXLagNPCWoodCutter::BeginBroachTree(AXLagCuttableTreeBase *targetTree)
{
	UE_LOG(LogTemp, Log, TEXT("Woodcutter broach the tree"));

	TargetTree = targetTree;
	IsCutting = false;
	IsBroaching = true;
}

void AXLagNPCWoodCutter::Cancel()
{
	TargetTree = nullptr;
	IsCutting = false;
	IsBroaching = false;
}

void AXLagNPCWoodCutter::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}
