#pragma once
#include "XLagTaskFactoryBase.h"
#include "XLagNPCTaskBase.h"
#include "XLagBlDigGraundTask.h"
#include "XLagBlPourGraundTask.h"
#include "XLagBlBuildTask.h"
#include "../../XLagDynamicTerrain/Position/MinMaxLevelPlace.h"
#include "../../XLagDynamicTerrain/XLagDynamicTerrainMapItemOperation.h"
#include "../../Common/ITerrainMapAccessor.h"

/*
 ������� ����� ��� ���������.
*/
class XLagBuilderTaskFactory : protected XLagTaskFactoryBase
{
public:
	XLagBuilderTaskFactory(std::shared_ptr<ITerrainMapAccessor> place)
		: Place(place)
	{
	}

	// ��������������� ��������.
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

					result->SubTasks.push_back(MoveTo(pos));
					result->SubTasks.push_back(Dig(i, j, current_lev, false));
				}

		return result;
	}

	// ��������������� ����������.
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

					result->SubTasks.push_back(MoveTo(pos));
					result->SubTasks.push_back(Pour(i, j, current_lev, element));
				}

		return result;
	}

	//  �������.
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

					result->SubTasks.push_back(MoveTo(pos));
					result->SubTasks.push_back(Dig(i, j, current_lev, false));
				}

		return result;
	}

	//  ���������.
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

					result->SubTasks.push_back(MoveTo(pos));
					result->SubTasks.push_back(Pour(i, j, current_lev, element));
				}

		return result;
	}

	//  ������� ����.
	std::shared_ptr<XLagNPCTaskBase> CleanLayerPlace()
	{
		auto result = std::make_shared<XLagNPCTaskBase>();

		auto maximalLocation = MinMaxLevelPlace(Place).FindMaximalLevel();
		auto maximalVector = Place->GetWorldPosition(maximalLocation.first, maximalLocation.second, GetPositionEnum::CenterHeghtPosition);
		auto cleaningLayerKind = XLagDynamicTerrainMapItemOperation(Place->Point(maximalLocation.first, maximalLocation.second)).GetTopKind();

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

					auto lh = XLagDynamicTerrainMapItemOperation(thisPoint).GetHeghtTopLevel();
					/*if (lh < 0.1)
						continue;*/

					auto current_lev = XLagDynamicTerrainMapItemOperation(thisPoint).GetTopLevel() - lh;
					auto pos = Place->GetWorldPosition(i, j, GetPositionEnum::CenterHeghtPosition);

					result->SubTasks.push_back(MoveTo(pos));
					result->SubTasks.push_back(Dig(i, j, current_lev, true));

					repeat = true;
				}
		}

		return result;
	}

	std::shared_ptr<XLagNPCTaskBase> Build(AXLagBuilding *building)
	{
		auto result = std::make_shared<XLagNPCTaskBase>();
		auto pos = building->GetActorLocation();

		result->SubTasks.push_back(MoveTo(pos));
		result->SubTasks.push_back(std::shared_ptr<XLagNPCTaskBase>(new XLagBlBuildTask(building)));
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