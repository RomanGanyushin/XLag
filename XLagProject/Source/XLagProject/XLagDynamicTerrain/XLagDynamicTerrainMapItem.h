#pragma once
#include <algorithm>
#include <vector>
#include <map>
#include <functional>

#include "XLagDynamicTerrainMapItemLayer.h"
#include "../Common/OnSurfaceResourceObjectsEnum.h"
#include "../Common/TerrainElementEnum.h"
#include "../XLagMinerals/Models/XLagMineralDesc.h"

class XLagDynamicTerrainMapItem
{
public:
	XLagDynamicTerrainMapItem() 
	{
		static long id_counter = 0;
		_id = id_counter++;
	}

private:
	std::vector<XLagDynamicTerrainMapItemLayer>  Stack;

	// Время затраченного на поиск ресурса.
	std::map<int, float> _resurceSearchTimeMap;
	
	// Идентификатор клетки.	
	long _id;
public:
	bool IsZeroLocation = false;
	bool Changed = false;
	
	const long GetId() const { return _id; }

	OnSurfaceResourceObjectsEnum OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Empty;

	void AddLayer(XLagDynamicTerrainMapItemLayer item)
	{
		if (Stack.empty())
		{
			Stack.push_back(item);
			return;
		}
		
		auto newItemLayer = item.GetLevel();
		auto upperItemLayer = std::find_if(Stack.begin(), Stack.end(), [newItemLayer](auto& it) { return it.GetLevel() > newItemLayer; });
		Stack.insert(upperItemLayer, item);
	}

	const XLagDynamicTerrainMapItemLayer* GetForLayerKind(TerrainElementEnum layerKind) const
	{
		if (Stack.empty())
			return nullptr;

		auto& top = Stack.back();
		if (!top.IsTerrainElement(layerKind))
			return nullptr;
	
		return &top;
	}

	const XLagDynamicTerrainMapItemLayer* Get() const
	{
		if (Stack.empty())
			return nullptr;

		return &Stack.back();
	}

	const float GetTopLevel() const
	{
		if (Stack.empty())
			return -10000.f;

		return Stack.back().GetLevel();
	}

	const int GetTopKind() const
	{
		if (Stack.empty())
			return -1;

		return Stack.back().GetTerrainElement();
	}

	void ChangeTopKind(TerrainElementEnum newKind)
	{
		if (Stack.empty())
			return;

		Stack.back().ChangeTerrainElement(newKind);
	}

	void ChangeAllKind(TerrainElementEnum newKind)
	{
		if (Stack.empty())
			return;

		for (auto& it : Stack)
			it.ChangeTerrainElement(newKind);
	}

	const bool CheckForMineral(int mineralId) const
	{
		return std::find_if(Stack.begin(), Stack.end(), [mineralId](auto& it)
		{ return it.GetMineralId() == mineralId; }) != Stack.end();
	}

	const float MeasureResourceQuantity(int mineralId) const
	{
		auto foundResourceItem = std::find_if(Stack.begin(), Stack.end(), [mineralId](auto& it)
		{ return it.GetMineralId() == mineralId; });

		if (foundResourceItem == Stack.end())
			return 0;

		if (foundResourceItem == Stack.begin())
			return 1; // Если это последний слой.

		auto nextItem = foundResourceItem - 1;
		return (foundResourceItem->GetLevel() - nextItem->GetLevel()) / 100.0;
	}

	void MoveTopLevelTo(float level)
	{
		if (Stack.empty())
			return;

		auto delta = level - GetTopLevel();
		for (auto &it : Stack)
		{
			it.ChangeLevel(it.GetLevel() + delta);
		}
	}

	const float GetHeghtTopLevel() const
	{
		if (Stack.size() < 2)
			return 100000;

		return Stack[Stack.size() - 1].GetLevel() - Stack[Stack.size() - 2].GetLevel();
	}


	void Dig(float value, bool keepTopLayer)
	{
		if (Stack.empty())
			return;

		auto currentLevel = Stack.back().GetLevel();
		auto newLevel = currentLevel - value;

		UE_LOG(LogTemp, Log, TEXT("Dig Info: SZ:%d"), Stack.size());

		//Снимаем слой если необходимо:
		if (!keepTopLayer)
		{
			while ((Stack.size() > 1) && (Stack[Stack.size() - 2].GetLevel() > newLevel))
			{
				UE_LOG(LogTemp, Log, TEXT("Dig: Delete layer"));
				Stack.pop_back();
			}

			auto element = GetTopKind();

			for (int i = 0; i < 8; i++)
				if (B[i] != nullptr && B[i]->GetTopKind() != element)
				{
					B[i]->ChangeTopKind(TransitionTerrainElementCatalog::For((TerrainElementEnum)B[i]->GetTopKind(), (TerrainElementEnum)element));
				}
		}
		else
		{
			if (Stack.size() >= 2)
			{
				newLevel = Stack[Stack.size() -2 ].GetLevel() + 0.05;
			}
			else
			{
				return;
			}		
		}

		Stack.back().ChangeLevel(newLevel);

		Changed = true;
	}

	void Pour(float value, TerrainElementEnum element)
	{
		if (Stack.empty())
			return;

		auto currentLevel = Stack.back().GetLevel();
		auto newLevel = currentLevel + value;

		////Добавляем слой если необходимо:
		if (GetTopKind() != element)
		{
			Stack.push_back(XLagDynamicTerrainMapItemLayer(newLevel, element));
		}
		else
		{
			for (int i=0; i< 8; i++)
			if (B[i] != nullptr && B[i]->GetTopKind() != element)
			{
				B[i]->ChangeTopKind(TransitionTerrainElementCatalog::For((TerrainElementEnum)B[i]->GetTopKind(), element));
			}
			
			Stack.back().ChangeLevel(newLevel);
		}
		
		Changed = true;
	}

	bool SearchResource(const FXLagMineralDesc& mineral, float force)
	{
		if (_resurceSearchTimeMap.find(mineral.ID) == _resurceSearchTimeMap.end())
		{
			_resurceSearchTimeMap[mineral.ID] = force;
		}
		else
		{
			_resurceSearchTimeMap[mineral.ID] += force;
		}

		if (_resurceSearchTimeMap[mineral.ID] < mineral.SearchComplexity)
			return false;

		if (CheckForMineral(mineral.ID)) // Если минерал уже есть, то ничего не делаем.
			return true;

		CreateMineralLayerEventRaise(this, mineral);
		return true;
	}

	const inline bool HasOnSurfaceResourceObjects(OnSurfaceResourceObjectsEnum type) const
	{
		return  OnSurfaceResourceObjects == type;
	}

	XLagDynamicTerrainMapItem* B[8];
	std::function<void(XLagDynamicTerrainMapItem*, const FXLagMineralDesc& mineral)> CreateMineralLayerEventRaise;
};
