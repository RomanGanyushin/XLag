#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "XLagBlDigGraundTask.h"
#include "XLagBlPourGraundTask.h"
#include "../XLagDynamicTerrain\Position/MinMaxLevelPlace.h"
#include "../Common/ITerrainMapAccessor.h"

/*
 Фабрика задач для строителя.
*/
class XLagBuilderTaskFactory
{
public:
	float CompliteDistanceToTree = 1.0f;
	float SpaceScale = 100.f;

public:
	XLagBuilderTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
		: Place(place)
	{
	}

	// Выравнивнивание копанием.
	std::shared_ptr<XLagNPCTaskBase> AlignDigPlace()
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto minimalLocation = MinMaxLevelPlace(Place).FindMinimalLevel();
		auto minimalVector = Place->GetWorldPosition(minimalLocation.first, minimalLocation.second, GetPositionEnum::CenterLowPosition);
		auto maximalLocation = MinMaxLevelPlace(Place).FindMaximalLevel();
		auto maximalVector = Place->GetWorldPosition(maximalLocation.first, maximalLocation.second, GetPositionEnum::CenterHeghtPosition);

		auto sliceHeight = maximalVector.Z - minimalVector.Z;
		auto maxSlice = 100;


		for (int n = 0; n < int(sliceHeight / maxSlice) + 1; n++)
			for (int i = 0; i <= Place->SizeX(); i++)
				for (int j = 0; j <= Place->SizeY(); j++)
				{
					auto current_lev = maximalVector.Z - maxSlice * n;
					current_lev = std::max(current_lev, minimalVector.Z);

					auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
					if (pos.Z < current_lev)
						continue;

					result->SubTasks.push(MoveTo(pos));
					result->SubTasks.push(Dig(i, j, current_lev, false));
				}

		return result;
	}

	// Выравнивнивание насыпанием.
	std::shared_ptr<XLagNPCTaskBase> AlignPourPlace(TerrainElementEnum element)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto minimalLocation = MinMaxLevelPlace(Place).FindMinimalLevel();
		auto minimalVector = Place->GetWorldPosition(minimalLocation.first, minimalLocation.second, GetPositionEnum::CenterLowPosition);
		auto maximalLocation = MinMaxLevelPlace(Place).FindMaximalLevel();
		auto maximalVector = Place->GetWorldPosition(maximalLocation.first, maximalLocation.second, GetPositionEnum::CenterHeghtPosition);

		auto sliceHeight = maximalVector.Z - minimalVector.Z;
		auto maxSlice = 100;

		for (int n = 0; n < int(sliceHeight / maxSlice) + 1; n++)
			for (int i = 0; i <= Place->SizeX(); i++)
				for (int j = 0; j <= Place->SizeY(); j++)
				{
					auto current_lev = minimalVector.Z + maxSlice * n;
					current_lev = std::min(current_lev, maximalVector.Z);

					auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
					
					/*if (pos.Z > current_lev - maxSlice)
						continue;

					if (pos.Z > current_lev)
					{
						current_lev = maximalVector.Z;
					}*/

					result->SubTasks.push(MoveTo(pos));
					result->SubTasks.push(Pour(i, j, current_lev, element));
				}

		return result;
	}

	//  Копание.
	std::shared_ptr<XLagNPCTaskBase> DigPlace(float sliceHeight)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto minimalLocation = MinMaxLevelPlace(Place).FindMinimalLevel();
		auto minimalVector = Place->GetWorldPosition(minimalLocation.first, minimalLocation.second, GetPositionEnum::CenterLowPosition);

		auto maxSlice = 100;

		for (int n = 0; n < int(sliceHeight / maxSlice) + 1; n++)
			for (int i = n /*+ 1*/; i <= Place->SizeX() - n /*- 1*/; i++)
				for (int j = n /*+ 1*/; j <= Place->SizeY() - n /*- 1*/; j++)
				{
					auto current_lev = minimalVector.Z - maxSlice * n;
					auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);

					result->SubTasks.push(MoveTo(pos));
					result->SubTasks.push(Dig(i, j, current_lev, false));
				}

		return result;
	}

	//  Насыпание.
	std::shared_ptr<XLagNPCTaskBase> PourPlace(float sliceHeight, TerrainElementEnum element)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto maximalLocation = MinMaxLevelPlace(Place).FindMaximalLevel();
		auto maximalVector = Place->GetWorldPosition(maximalLocation.first, maximalLocation.second, GetPositionEnum::CenterHeghtPosition);

		auto maxSlice = 100;

		for (int n = 0; n < int(sliceHeight / maxSlice) + 1; n++)
			for (int i = n; i <= Place->SizeX() - n /*- 1*/; i++)
				for (int j = n; j <= Place->SizeY() - n /*- 1*/; j++)
				{
					auto current_lev = maximalVector.Z + maxSlice * n;
					auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);

					result->SubTasks.push(MoveTo(pos));
					result->SubTasks.push(Pour(i, j, current_lev, element));
				}

		return result;
	}

	//  Очистка слоя.
	std::shared_ptr<XLagNPCTaskBase> CleanLayerPlace()
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto maximalLocation = MinMaxLevelPlace(Place).FindMaximalLevel();
		auto maximalVector = Place->GetWorldPosition(maximalLocation.first, maximalLocation.second, GetPositionEnum::CenterHeghtPosition);
		auto cleaningLayerKind = Place->Point(maximalLocation.first, maximalLocation.second).GetTopKind();

		auto maxSlice = 50;

		bool repeat = true;
		//for (int n = 1; n <= 2; n++)
		{
			repeat = false;
			for (int i = 0; i < Place->SizeX(); i++)
				for (int j = 0; j < Place->SizeY(); j++)
				{
					auto thisPoint = Place->Point(i, j);

					//if (thisPoint.GetTopKind() != cleaningLayerKind)
					//	continue;

					auto lh = thisPoint.GetHeghtTopLevel();
					/*if (lh < 0.1)
						continue;*/

					auto current_lev = thisPoint.GetTopLevel() - lh;
					auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);

					result->SubTasks.push(MoveTo(pos));
					result->SubTasks.push(Dig(i, j, current_lev, true));

					repeat = true;
				}
		}

		return result;
	}


	// Двигайся до указанной локации.
	// Todo: вынести в базовый.
	std::shared_ptr<XLagNPCTaskBase> MoveTo(const FVector& location)
	{
		auto result = std::shared_ptr<XLagNPCTaskBase>(new XLagNPCTaskMoveTo(location, CompliteDistanceToTree * SpaceScale, 10));
		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Dig(int x, int y, float level, bool keepTopLayer)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagBlDigGraundTask(Place, x, y, level, keepTopLayer));
	}

	std::shared_ptr<XLagNPCTaskBase> Pour(int x, int y, float level, TerrainElementEnum element)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagBlPourGraundTask(Place, x, y, level, element));
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};