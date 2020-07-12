#include "XLagDynamicTerrainMapWindow.h"

// #inhereddoc
XLagDynamicTerrainMapWindow::XLagDynamicTerrainMapWindow(ITerrainMapAccessor *map, int off_x, int off_y, int width, int height)
	:_fullMap(map), _width(width), _height(height), _offsetX(off_x), _offsetY(off_y)
{
	if (_fullMap == nullptr)
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
	}
}

std::shared_ptr<ITerrainMapAccessor> XLagDynamicTerrainMapWindow::CreateWindow(int const &x, int const &y, int const &sx, int const &sy)
{
	return std::shared_ptr<ITerrainMapAccessor>(new XLagDynamicTerrainMapWindow(_fullMap, x + _offsetX, y + _offsetY, sx, sy));
}

// #inhereddoc
XLagDynamicTerrainMapItem& XLagDynamicTerrainMapWindow::Point(int const &x, int const &y)
{ 
	return _fullMap->Point(x + _offsetX, y + _offsetY);
}

// #inhereddoc
XLagDynamicTerrainMapItem& XLagDynamicTerrainMapWindow::Point(int const &index)
{
	// TODO: Сделать вычисления.
	throw std::exception();
}

const XLagDynamicTerrainMapItem& XLagDynamicTerrainMapWindow::PointConst(int const &x, int const &y) const
{
	return _fullMap->Point(x + _offsetX, y + _offsetY);
}

const FVector XLagDynamicTerrainMapWindow::GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const
{
	return _fullMap->GetWorldPosition(x + _offsetX, y + _offsetY, flag);
}

const FVector XLagDynamicTerrainMapWindow::GetWorldPosition(XLagDynamicTerrainMapItem* item, GetPositionEnum flag) const
{
	return _fullMap->GetWorldPosition(item, flag);
}


std::vector<XLagDynamicTerrainMapItem*> XLagDynamicTerrainMapWindow::GetFilteredItems(const IMapItemFilter& filter)
{
	return _fullMap->GetFilteredItems(filter);
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