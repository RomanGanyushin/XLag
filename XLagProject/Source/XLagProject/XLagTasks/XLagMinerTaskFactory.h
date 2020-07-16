#pragma once

#include "XLagNPCTaskBase.h"
#include "XLagNPCTaskMoveTo.h"
#include "XLagMIDigGraundTask.h"
#include "XLagMIPourGraundTask.h"
#include "../XLagDynamicTerrain\Position/MinMaxLevelPlace.h"
#include "../Common/ITerrainMapAccessor.h"

/*
 Фабрика задач для шахтера.
*/
class XLagMinerTaskFactory
{
public:
	float CompliteDistanceToTree = 1.0f;
	float SpaceScale = 100.f;

public:
	XLagMinerTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
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
		auto maxSlice = 50;

	/*	for (int i = 0; i < Place->SizeX(); i++)
			for (int j = 0; j < Place->SizeY(); j++)
			{
				 if ((i == 0 || i == Place->SizeX() -1) || (j == 0 || j == Place->SizeY() - 1))
					 {
						 Place->Point(i, j).ChangeAllKind(4);
					 }
			}*/

		for(int n = 0; n < int(sliceHeight / maxSlice) + 1; n++)
		for (int i = 0; i< Place->SizeX()  ; i++)
			for (int j = 0; j < Place->SizeY() ; j++)
			{
				auto current_lev = maximalVector.Z - maxSlice * n;
				current_lev = std::max(current_lev, minimalVector.Z);

				auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
				if (pos.Z < current_lev)
					continue;

				result->SubTasks.push(MoveTo(pos));
				result->SubTasks.push(Dig(i, j, current_lev));
			}	
		
		return result;
	}

	// Выравнивнивание копанием.
	std::shared_ptr<XLagNPCTaskBase> AlignPourPlace(TerrainElementEnum element)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto minimalLocation = MinMaxLevelPlace(Place).FindMinimalLevel();
		auto minimalVector = Place->GetWorldPosition(minimalLocation.first, minimalLocation.second, GetPositionEnum::CenterLowPosition);
		auto maximalLocation = MinMaxLevelPlace(Place).FindMaximalLevel();
		auto maximalVector = Place->GetWorldPosition(maximalLocation.first, maximalLocation.second, GetPositionEnum::CenterHeghtPosition);

		auto sliceHeight = maximalVector.Z - minimalVector.Z;
		auto maxSlice = 50;

		for (int n = 0; n < int(sliceHeight / maxSlice) + 1; n++)
			for (int i = 0; i < Place->SizeX(); i++)
				for (int j = 0; j < Place->SizeY(); j++)
				{
					auto current_lev = minimalVector.Z + maxSlice * n;
					current_lev = std::min(current_lev, maximalVector.Z);

					auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);
					if (pos.Z > current_lev)
						continue;

					result->SubTasks.push(MoveTo(pos));
					result->SubTasks.push(Pour(i, j, current_lev, element));
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

	std::shared_ptr<XLagNPCTaskBase> Dig(int x, int y, float level)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagMIDigGraundTask(Place, x, y, level));
	}

	std::shared_ptr<XLagNPCTaskBase> Pour(int x, int y, float level, TerrainElementEnum element)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagMIPourGraundTask(Place, x, y, level, element));
	}

	std::shared_ptr<XLagNPCTaskBase> Inc(int x, int y, float level)
	{
		return std::shared_ptr<XLagNPCTaskBase>(new XLagMIDigGraundTask(Place, x, y, level));
	}

private:
	std::shared_ptr<ITerrainMapAccessor> Place;
};