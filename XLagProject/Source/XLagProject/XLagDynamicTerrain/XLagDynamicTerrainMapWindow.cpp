#include "XLagDynamicTerrainMapWindow.h"

// #inhereddoc
XLagDynamicTerrainMapWindow::XLagDynamicTerrainMapWindow(ITerrainMapAccessor *map, int off_x, int off_y, int width, int height)
	:_fullMap(map), _width(width), _height(height), _offsetX(off_x), _offsetY(off_y)
{
	/*if (_fullMap == nullptr)
	{
		throw std::exception();
	}

	if (_width <= 0 && _width >= _fullMap->SizeX())
	{
		throw std::exception();
	}

	if (_height <= 0 && _height >= _fullMap->SizeY())
	{
		throw std::exception();
	}*/
}

std::shared_ptr<ITerrainMapAccessor> XLagDynamicTerrainMapWindow::CreateWindow(int const &x, int const &y, int const &sx, int const &sy)
{
	return std::shared_ptr<ITerrainMapAccessor>(new XLagDynamicTerrainMapWindow(_fullMap, x + _offsetX, y + _offsetY, sx, sy));
}

// #inhereddoc
FXLagDynamicTerrainMapItem& XLagDynamicTerrainMapWindow::Point(int const &x, int const &y)
{ 
	return _fullMap->Point(x + _offsetX, y + _offsetY);
}

// #inhereddoc
FXLagDynamicTerrainMapItem& XLagDynamicTerrainMapWindow::Point(int const &index)
{
	// TODO: Сделать вычисления.
	return _fullMap->Point(index);
}

const FXLagDynamicTerrainMapItem& XLagDynamicTerrainMapWindow::PointConst(int const &x, int const &y) const
{
	return _fullMap->Point(x + _offsetX, y + _offsetY);
}

const FVector XLagDynamicTerrainMapWindow::GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const
{
	return _fullMap->GetWorldPosition(x + _offsetX, y + _offsetY, flag);
}

const FVector XLagDynamicTerrainMapWindow::GetWorldPosition(FXLagDynamicTerrainMapItem* item, GetPositionEnum flag) const
{
	return _fullMap->GetWorldPosition(item, flag);
}

const FVector XLagDynamicTerrainMapWindow::GetWorldPosition(const CoordinatePoint& coord, GetPositionEnum flag) const
{
	return GetWorldPosition(coord.X, coord.Y, flag);
}

const FVector XLagDynamicTerrainMapWindow::GetWorldPosition(const int32 index, GetPositionEnum flag) const
{
	return _fullMap->GetWorldPosition(index, flag);
}

std::vector<FXLagDynamicTerrainMapItem*> XLagDynamicTerrainMapWindow::GetFilteredItems(const IMapItemFilter& filter)
{
	std::vector<FXLagDynamicTerrainMapItem*> result;

	for (int ix = 0; ix < SizeX(); ix++)
		for (int iy = 0; iy < SizeX(); iy++)
		{
			auto& item = Point(ix, iy);

			if (filter.IsMatch(item))
			{
				result.push_back(&item);
			}
		}

	return result;
}

bool XLagDynamicTerrainMapWindow::IsChanged()
{
	bool result = false;
	for (int ix = 0; ix < SizeX(); ix++)
		for (int iy = 0; iy < SizeX(); iy++)
		{
			if (Point(ix, iy).Changed)
			{
				result = true;
				Point(ix, iy).Changed = false;
			}
		}



	return result;
}

const CoordinatePoint XLagDynamicTerrainMapWindow::GetCoordinate(FXLagDynamicTerrainMapItem* item) const
{
	//throw std::exception(); //TODO: Впринуипе нужно только учесть смещение.
	return _fullMap->GetCoordinate(item);
}