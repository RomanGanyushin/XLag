#include "XLagNPCBuilderman.h"
#include "../BuildDefinition.h"
#include "../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"

void AXLagNPCBuilderman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDiging && digMemo.get() != nullptr)
	{
		auto targetSlice = XLagDynamicTerrainMapItemOperation(*digMemo->targetCell).GetTopLevel() - digMemo->ToLevel;

		UE_LOG(LogTemp, Log, TEXT("Dig target slice %f"), targetSlice);

		if (targetSlice <= 0)
			return;

		targetSlice = std::min(targetSlice, 0.01f * DEBUG_FORCE_MULTIPLIER);

		XLagDynamicTerrainMapItemOperation(*digMemo->targetCell).Dig(targetSlice, digMemo->KeepTopLayer);
	}

	if (IsPouring && pourMemo.get() != nullptr)
	{
		auto targetSlice = pourMemo->ToLevel - XLagDynamicTerrainMapItemOperation(*pourMemo->targetCell).GetTopLevel();

		UE_LOG(LogTemp, Log, TEXT("Dig target slice %f"), targetSlice);

		if (targetSlice <= 0)
			return;

		targetSlice = std::min(targetSlice, 0.01f * DEBUG_FORCE_MULTIPLIER);

		XLagDynamicTerrainMapItemOperation(*pourMemo->targetCell).Pour(targetSlice, pourMemo->Element);
	}
}

void AXLagNPCBuilderman::Dig(FXLagDynamicTerrainMapItem& cell, float toLevel, bool keepTopLayer)
{
	IsDiging = true;
	digMemo = std::shared_ptr<DigMemo>(new DigMemo(&cell, toLevel, keepTopLayer));
}

void AXLagNPCBuilderman::Pour(FXLagDynamicTerrainMapItem& cell, float toLevel, TerrainElementEnum element)
{
	IsPouring = true;
	pourMemo = std::shared_ptr<PourMemo>(new PourMemo(&cell, toLevel, element));
}

void AXLagNPCBuilderman::Build(AXLagBuilding* building)
{
	IsBuilding = true;
	building->Build();
}

void AXLagNPCBuilderman::Cancel()
{
	digMemo.reset();
	pourMemo.reset();
	IsDiging = false;
	IsPouring = false;
	IsBuilding = true;
}

void AXLagNPCBuilderman::OfferAccept(UXLagTaskBase* task)
{
	AXLagNPCBase::OfferAccept(task);
}