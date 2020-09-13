// Fill out your copyright notice in the Description page of Project Settings.


#include "XLagNPCBuilderman.h"


void AXLagNPCBuilderman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDiging && digMemo.get() != nullptr)
	{
		auto targetSlice = digMemo->targetCell->GetTopLevel() - digMemo->ToLevel;

		UE_LOG(LogTemp, Log, TEXT("Dig target slice %f"), targetSlice);

		if (targetSlice <= 0)
			return;

		targetSlice = std::min(targetSlice, 5.f);

		digMemo->targetCell->Dig(targetSlice, digMemo->KeepTopLayer);
	}

	if (IsPouring && pourMemo.get() != nullptr)
	{
		auto targetSlice = pourMemo->ToLevel - pourMemo->targetCell->GetTopLevel();

		UE_LOG(LogTemp, Log, TEXT("Dig target slice %f"), targetSlice);

		if (targetSlice <= 0)
			return;

		targetSlice = std::min(targetSlice, 5.f);

		pourMemo->targetCell->Pour(targetSlice, pourMemo->Element);
	}
}

void AXLagNPCBuilderman::Dig(XLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer)
{
	IsDiging = true;
	digMemo = std::shared_ptr<DigMemo>(new DigMemo(&cell, toLevel, keepTopLayer));
}

void AXLagNPCBuilderman::Pour(XLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element)
{
	IsPouring = true;
	pourMemo = std::shared_ptr<PourMemo>(new PourMemo(&cell, toLevel, element));
}

void AXLagNPCBuilderman::Cancel()
{
	digMemo.reset();
	pourMemo.reset();
	IsDiging = false;
	IsPouring = false;
}

void AXLagNPCBuilderman::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}