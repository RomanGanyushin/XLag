#pragma once
#include "XLagDynamicTerrainMapItem.h"
#include "XLagDynamicTerrainMapItemLayer.h"
#include "../XLagMinerals/Models/XLagMineralDesc.h"

class XLagDynamicTerrainMapItemOperation
{
public:
	XLagDynamicTerrainMapItemOperation(FXLagDynamicTerrainMapItem& mapItem)
		:MapItem(mapItem)
	{
	}

	XLagDynamicTerrainMapItemOperation(const FXLagDynamicTerrainMapItem& mapItem)
		:MapItem(const_cast<FXLagDynamicTerrainMapItem&>(mapItem))
	{
	}

	void AddLayer(FXLagDynamicTerrainMapItemLayer item)
	{
		if (MapItem.Stack.Num() == 0)
		{
			MapItem.Stack.Add(item);
			return;
		}

		auto newItemLayer = item.Level;
		auto upperItemLayer = MapItem.Stack.IndexOfByPredicate([newItemLayer](auto& it) { return it.Level > newItemLayer; });
		MapItem.Stack.Insert(item, upperItemLayer);
	}

	FXLagDynamicTerrainMapItemLayer* GetForLayerKind(TerrainElementEnum layerKind)
	{
		if (MapItem.Stack.Num() == 0)
			return nullptr;

		auto& top = MapItem.Stack.Last();
		if (!top.Element == layerKind)
			return nullptr;

		return &top;
	}

	const FXLagDynamicTerrainMapItemLayer* Get() const
	{
		if (MapItem.Stack.Num() == 0)
			return nullptr;

		return &MapItem.Stack.Last();
	}

	const float GetTopLevel() const
	{
		if (MapItem.Stack.Num() == 0)
			return -10000.f;

		return MapItem.Stack.Last().Level;
	}

	const TerrainElementEnum GetTopKind() const
	{
		if (MapItem.Stack.Num() == 0)
			return TerrainElementEnum::None;

		return MapItem.Stack.Last().Element.GetValue();
	}

	void ChangeTopKind(TerrainElementEnum newKind)
	{
		if (MapItem.Stack.Num() == 0)
			return;

		MapItem.Stack.Last().Element = newKind;
	}

	void ChangeAllKind(TerrainElementEnum newKind)
	{
		if (MapItem.Stack.Num() == 0)
			return;

		for (auto& it : MapItem.Stack)
			it.Element = newKind;
	}

	const bool CheckForMineral(int mineralId) const
	{
		auto condition = [mineralId](auto& it) { return it.MineralId == mineralId; };
		return MapItem.Stack.ContainsByPredicate(condition);
	}

	const float MeasureResourceQuantity(int mineralId) const
	{
		auto filter = [mineralId](auto& it) { return it.MineralId == mineralId; };
		auto foundResourceItemIndex = MapItem.Stack.IndexOfByPredicate(filter);

		if (foundResourceItemIndex == INDEX_NONE)
			return 0;

		if (foundResourceItemIndex == 0) 
			return 1; // Если это последний слой.

		auto nextItem = MapItem.Stack[foundResourceItemIndex - 1];
		return (MapItem.Stack[foundResourceItemIndex].Level - nextItem.Level) / 100.0;
	}

	void MoveTopLevelTo(float level)
	{
		if (MapItem.Stack.Num() == 0)
			return;

		auto delta = level - GetTopLevel();
		for (auto &it : MapItem.Stack)
		{
			it.Level = it.Level + delta;
		}
	}

	const float GetHeghtTopLevel() const
	{
		if (MapItem.Stack.Num() < 2)
			return 100000;

		return MapItem.Stack[MapItem.Stack.Num() - 1].Level - MapItem.Stack[MapItem.Stack.Num() - 2].Level;
	}


	void Dig(float value, bool keepTopLayer)
	{
		if (MapItem.Stack.Num() == 0)
			return;

		auto currentLevel = MapItem.Stack.Last().Level;
		auto newLevel = currentLevel - value;

		UE_LOG(LogTemp, Log, TEXT("Dig Info: SZ:%d"), MapItem.Stack.Num());

		//Снимаем слой если необходимо:
		if (!keepTopLayer)
		{
			while ((MapItem.Stack.Num() > 1) && (MapItem.Stack[MapItem.Stack.Num() - 2].Level > newLevel))
			{
				UE_LOG(LogTemp, Log, TEXT("Dig: Delete layer"));
				MapItem.Stack.RemoveAt(MapItem.Stack.Num() - 1);
			}

			auto element = GetTopKind();

			for (int i = 0; i < 8; i++)
			{
				XLagDynamicTerrainMapItemOperation bi(*MapItem.B[i]);

				if (MapItem.B[i] != nullptr && bi.GetTopKind() != element)
				{
					bi.ChangeTopKind(TransitionTerrainElementCatalog::For(bi.GetTopKind(), (TerrainElementEnum)element));
				}
			}	
		}
		else
		{
			if (MapItem.Stack.Num() >= 2)
			{
				newLevel = MapItem.Stack[MapItem.Stack.Num() - 2].Level + 0.05;
			}
			else
			{
				return;
			}
		}

		MapItem.Stack.Last().Level = newLevel;

		MapItem.Changed = true;
	}

	void Pour(float value, TerrainElementEnum element)
	{
		if (MapItem.Stack.Num() == 0)
			return;

		auto currentLevel = MapItem.Stack.Last().Level;
		auto newLevel = currentLevel + value;

		////Добавляем слой если необходимо:
		if (GetTopKind() != element)
		{
			MapItem.Stack.Add(FXLagDynamicTerrainMapItemLayer(newLevel, element));
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				if (MapItem.B[i] == nullptr)
					continue;

				XLagDynamicTerrainMapItemOperation bi(*MapItem.B[i]);
				if (bi.GetTopKind() != element)
				{
					bi.ChangeTopKind(TransitionTerrainElementCatalog::For(bi.GetTopKind(), element));
				}
			}
				
			MapItem.Stack.Last().Level = newLevel;
		}

		MapItem.Changed = true;
	}

	bool SearchResource(const FXLagMineralDesc& mineral, float force)
	{
		if (!MapItem.ResurceSearchTimeMap.Contains(mineral.ID))
		{
			MapItem.ResurceSearchTimeMap.Add(mineral.ID, force);
		}
		else
		{
			MapItem.ResurceSearchTimeMap[mineral.ID] += force;
		}

		if (MapItem.ResurceSearchTimeMap[mineral.ID] < mineral.SearchComplexity)
			return false;

		if (CheckForMineral(mineral.ID)) // Если минерал уже есть, то ничего не делаем.
			return true;

		MapItem.CreateMineralLayerEventRaise(&MapItem, mineral);
		return true;
	}

	float ExtractResource(const FXLagMineralDesc& mineral, float force)
	{
		if (!CheckForMineral(mineral.ID)) // Если минерала нет, то ничего не делаем.
			return 0.0f;

		// Объем добычи обратнопропорционален трудоемкости.
		float extractedLayerHeight = mineral.MiningComplexity != 0.0 ? force / mineral.MiningComplexity : force;

		auto currentLevel = MapItem.Stack.Last().Level;
		auto newLevel = currentLevel - extractedLayerHeight;
		//Stack.back().ChangeLevel(newLevel);
		Dig(extractedLayerHeight, false);
		MapItem.Changed = true;

		return extractedLayerHeight / 2; // Заиспользовать настройки.
	}

	const inline bool HasOnSurfaceResourceObjects(OnSurfaceResourceObjectsEnum type) const
	{
		return  MapItem.OnSurfaceResourceObjects == type;
	}

private:
	FXLagDynamicTerrainMapItem& MapItem;
};