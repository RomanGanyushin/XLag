#pragma once
#include <vector>
#include "../../XLagProject//Common/OnSurfaceResourceObjectsEnum.h"
#include "MapBuilder\TerrainElementEnum.h"

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
private:
	std::vector<TerrainMapItemLevel>  Stack;

public:
	bool IsZeroLocation = false;
	bool Changed = false;

	OnSurfaceResourceObjectsEnum OnSurfaceResourceObjects = OnSurfaceResourceObjectsEnum::Empty;

	void AddLayer(TerrainMapItemLevel item)
	{
		auto trd = item;
		trd.ChangeKind(3);
		trd.ChangeLevel(trd.GetLevel() - 100);
		Stack.push_back(trd);
		Stack.push_back(item);
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

		//Снимаем слой если необходимо:
		if (!keepTopLayer)
		{
			while ((Stack.size() > 1) && (Stack[Stack.size() - 2].GetLevel() > newLevel))
			{
				UE_LOG(LogTemp, Log, TEXT(">>>>>>>>>>>>>> Delete layer >>>>>>>>>>>>>>>>>>>>>>>>>>>>"));
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

	const inline bool HasOnSurfaceResourceObjects(OnSurfaceResourceObjectsEnum type) const
	{
		return  OnSurfaceResourceObjects == type;
	}

	XLagDynamicTerrainMapItem* B[8];
};