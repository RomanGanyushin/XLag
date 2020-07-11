// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagNPCWoodCutter.h"

void AXLagNPCWoodCutter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLagNPCWoodCutter::DoCutTree(AXLagCuttableTreeBase *TargetTree)
{
	UE_LOG(LogTemp, Log, TEXT("Woodcutter cut the tree"));
	TargetTree->Cut(1);
	OnCuttingEvent(1.f);
}

void AXLagNPCWoodCutter::DoBroachTree(AXLagCuttableTreeBase *TargetTree)
{
	UE_LOG(LogTemp, Log, TEXT("Woodcutter broach the tree"));
	TargetTree->Broach(1);
	OnBroachingEvent(1.f);
}
