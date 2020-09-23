#include "XLagDynamicTerrainMap.h"
#include "XLagDynamicTerrainMapWindow.h"
#include <algorithm>

XLagDynamicTerrainMap::XLagDynamicTerrainMap(int sizeX, int sizeY, int scale)
	: Scale(scale), _sizeX(sizeX), _sizeY (sizeY)
{
}

void XLagDynamicTerrainMap::Initialize()
{
	Map = new XLagDynamicTerrainMapItem[MapLenght()];

	for (int x = 0; x <_sizeX; x++)
		for (int y = 0; y < _sizeY; y++)
		{
			Point(x, y).B[0] = &Point(SafeX(x - 1), SafeY(y - 1));
			Point(x, y).B[1] = &Point(SafeX(x - 1), SafeY(y));
			Point(x, y).B[2] = &Point(SafeX(x - 1), SafeY(y + 1));
			Point(x, y).B[3] = &Point(SafeX(x ), SafeY(y + 1));
			Point(x, y).B[4] = &Point(SafeX(x + 1), SafeY(y + 1));
			Point(x, y).B[5] = &Point(SafeX(x + 1), SafeY(y));
			Point(x, y).B[6] = &Point(SafeX(x + 1), SafeY(y -1 ));
			Point(x, y).B[7] = &Point(SafeX(x), SafeY(y + 1));

			Point(x, y).CreateMineralLayerEventRaise = std::bind(
				&XLagDynamicTerrainMap::CreateMineralLayerEventHandler,
				this,
				std::placeholders::_1,
				std::placeholders::_2);
		}
}

std::shared_ptr<ITerrainMapAccessor> XLagDynamicTerrainMap::CreateWindow(int const &x, int const &y, int const &sx, int const &sy)
{
	return std::make_shared<XLagDynamicTerrainMapWindow>(this, x, y, sx, sy);
}

const FVector XLagDynamicTerrainMap::GetWorldPosition(int const &x, int const &y, GetPositionEnum flag) const
{
	auto lev00 = PointConst(SafeX(x), SafeY(y)).GetTopLevel();
	auto lev01 = PointConst(SafeX(x), SafeY(y + 1)).GetTopLevel();
	auto lev11 = PointConst(SafeX(x + 1), SafeY(y + 1)).GetTopLevel();
	auto lev10 = PointConst(SafeX(x + 1), SafeY(y)).GetTopLevel();

	switch (flag)
	{
		case GetPositionEnum::CenterLowPosition:
			return FVector(x * Scale + Scale / 2.f, y * Scale + Scale / 2.f, std::min(std::min(lev00, lev01), std::min(lev11, lev10)));

		case GetPositionEnum::CenterHeghtPosition:
			return FVector(x * Scale + Scale / 2.f, y * Scale + Scale / 2.f, std::max(std::max(lev00, lev01), std::max(lev11, lev10)));

		case GetPositionEnum::LeftTopPosition:
			return FVector(x * Scale, (y + 1) * Scale, lev01);

		case GetPositionEnum::LeftBottomPosition:
			return FVector(x * Scale, y * Scale, lev00);

		case GetPositionEnum::RightTopPosition:
			return FVector((x + 1) * Scale, (y + 1) * Scale, lev11);

		case GetPositionEnum::RightBottomPosition:
			return FVector((x + 1) * Scale, y * Scale, lev10);

		default:
			return FVector();
	}
}

const FVector XLagDynamicTerrainMap::GetWorldPosition(XLagDynamicTerrainMapItem* item, GetPositionEnum flag) const
{
	const auto coord = GetCoordinate(item);
	return GetWorldPosition(coord.X, coord.Y, flag);
}

// #inhereddoc
std::vector<XLagDynamicTerrainMapItem*> XLagDynamicTerrainMap::GetFilteredItems(const IMapItemFilter& filter)
{
	std::vector<XLagDynamicTerrainMapItem*> result;

	for (auto index = 0; index < MapLenght(); index++)
	{
		if (!filter.IsMatch(Map[index]))
			continue;

		result.push_back(&Map[index]);
	}

	return result;
}


bool XLagDynamicTerrainMap::IsChanged()
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

void XLagDynamicTerrainMap::CreateMineralLayerEventHandler(XLagDynamicTerrainMapItem* sender, const FXLagMineralDesc& mineral)
{
	auto mineralGenDesc = mineral.OccurrenceMeneralGenDesc;

	if (mineralGenDesc.UnderTerrainElement != sender->GetTopKind()) // Проверяем условие залегания.
		return;

	auto coord = GetCoordinate(sender);
	auto analystSize = 10;
	auto analystRect = CoordinateRect(SafeX(coord.X - analystSize), SafeY(coord.Y - analystSize),
		SafeX(coord.X + analystSize), SafeY(coord.Y + analystSize));

	float aroundMineralQuantity = 0.0f;

	for (int x = analystRect.Point1.X; x <= analystRect.Point2.X; x++)
		for (int y = analystRect.Point1.Y; y <= analystRect.Point2.Y; y++)
			aroundMineralQuantity += PointConst(x, y).MeasureResourceQuantity(mineral.MineralTerrainElement);

	float currentMineralAvvarage = aroundMineralQuantity / analystRect.Square();
	
	if (currentMineralAvvarage != 0.0f/*> mineralGenDesc.AverageQuantity*/) // Если плотность минералов выше, то игнорируем генерацию.
		return;


	auto resurceRect = CoordinateRect(SafeX(coord.X - 3), SafeY(coord.Y - 3),
		SafeX(coord.X + 3), SafeY(coord.Y + 3));

	 for (int x = resurceRect.Point1.X; x <= resurceRect.Point2.X; x++) // Делаем костыльное месторождение.
		for (int y = resurceRect.Point1.Y; y <= resurceRect.Point2.Y; y++)
		{
			auto& item = Point(x, y);

			if (mineralGenDesc.UnderTerrainElement != TerrainElementEnum::None
				&& item.GetTopKind() != mineralGenDesc.UnderTerrainElement) // Проверяем условие верхнего элемента.
				continue;

			auto level = item.GetTopLevel();
			item.AddLayer(XLagDynamicTerrainMapItemLayer(level - 10, mineral.MineralTerrainElement, mineral.ID));
			item.AddLayer(XLagDynamicTerrainMapItemLayer(level - 200, TerrainElementEnum::RockBasalt));
			item.Changed = true;
		}		
}