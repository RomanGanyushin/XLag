#pragma once
#include <vector>
#include <map>
#include "../Common/OnSurfaceResourceObjectsEnum.h"
#include "../Common/TerrainElementEnum.h"
#include "../XLagMinerals/Models/XLagMineralDesc.h"

class TerrainMapItemLevel
{
public:
	TerrainMapItemLevel(float level, int layerKind)
		:_level(level), _layerKind(layerKind)
	{
	}

	inline bool IsLayerKind(const int layerKind) const { return layerKind == _layerKind; }
	inline const float GetLevel() const { return _level; }
	inline void ChangeLevel(const float& newLevel) { _level = newLevel; }
	inline const int GetKind() const { return _layerKind; }
	inline void ChangeKind(const int& newKind) { _layerKind = newKind; }

private:
	float _level;
	int _layerKind;
};

class XLagDynamicTerrainMapItem
{
public:
	XLagDynamicTerrainMapItem() 
	{
		static long id_counter = 0;
		_id = id_counter++;
	}

private:
	std::vector<TerrainMapItemLevel>  Stack;

	// Время затраченного на поиск ресурса.
	std::map<int, float> _resurceSearchTimeMap;
	
	// Идентификатор клетки.	
	long _id;
public:
	bool IsZeroLocation = false;
	bool Changed = false;
	
	const long GetId() const { return _id; }

	OnSurfaceResourceObjectsEnum OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Empty;

	void AddLayer(TerrainMapItemLevel item)
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

	const TerrainMapItemLevel* GetForLayerKind(int layerKind) const
	{
		if (Stack.empty())
			return nullptr;

		auto& top = Stack.back();
		if (!top.IsLayerKind(layerKind))
			return nullptr;
	
		return &top;
	}

	const TerrainMapItemLevel* Get() const
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

		return Stack.back().GetKind();
	}

	void ChangeTopKind(int newKind)
	{
		if (Stack.empty())
			return;

		Stack.back().ChangeKind(newKind);
	}

	void ChangeAllKind(int newKind)
	{
		if (Stack.empty())
			return;

		for (auto& it : Stack)
			it.ChangeKind(newKind);
	}

	const bool CheckForKind(int kind) const
	{
		return std::find_if(Stack.begin(), Stack.end(), [kind](auto& it)
		{ return it.IsLayerKind(kind); }) != Stack.end();
	}

	const float MeasureResourceQuantity(int kind) const
	{
		auto foundResourceItem = std::find_if(Stack.begin(), Stack.end(), [kind](auto& it)
		{ return it.IsLayerKind(kind); });

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
			Stack.push_back(TerrainMapItemLevel(newLevel, element));
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

		if (CheckForKind(mineral.MineralTerrainElement)) // Если минерал уже есть, то ничего не делаем.
			return true;

		CreateMineralLayerEventRaise(this, mineral);

		TerrainMapItemLevel new_it(GetTopLevel() - 10, 3);
		Stack.insert(Stack.begin(), new_it);
		return true;
	}

	const inline bool HasOnSurfaceResourceObjects(OnSurfaceResourceObjectsEnum type) const
	{
		return  OnSurfaceResourceObjects == type;
	}

	XLagDynamicTerrainMapItem* B[8];
	std::function<void(XLagDynamicTerrainMapItem*, const FXLagMineralDesc& mineral)> CreateMineralLayerEventRaise;
};