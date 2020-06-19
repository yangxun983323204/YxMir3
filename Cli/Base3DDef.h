#pragma once
#include <stdint.h>
#include <math.h>
#include <tuple>

const uint16_t CellW = 48;
const uint16_t CellH = 32;
const uint16_t HalfCW = CellW / 2;
const uint16_t HalfCH = CellH / 2;
const uint8_t CellPerTileX = 2;
const uint8_t CellPerTileY = 2;
const uint16_t TileW = CellW * CellPerTileX;
const uint16_t TileH = CellH * CellPerTileY;
const uint16_t CellCountX = 17;// 为了让角色居中，因此让屏幕水平和竖直方向都显示奇数个格子
const uint16_t CellCountY = 17;
const uint16_t LayoutW = CellW * CellCountX;// todo 必须为800*600，不然UI对应不上位置
const uint16_t LayoutH = CellH * CellCountY;
const float PI = 3.1415926f;
const float Rad2Deg = (360 / (PI * 2));

template<typename T>
struct Vector2
{
	T x;
	T y;
	bool operator ==(const Vector2<T> &v2)
	{
		return this->x == v2.x && this->y == v2.y;
	}
	static double Distance(Vector2<T> &v1, Vector2<T> &v2)
	{
		return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
	}
};

using Vector2UInt = Vector2<uint32_t>;
using Vector2Int = Vector2<int32_t>;
using Vector2Byte = Vector2<int8_t>;
using Vector2Float = Vector2<float>;

inline Vector2UInt World2Cell(Vector2Float world)
{
	return Vector2UInt{ (uint32_t)floor(world.x / CellW),(uint32_t)floor(world.y / CellH) };
}

inline Vector2Float Cell2World(Vector2UInt cell)
{
	return Vector2Float{ (float)(cell.x * CellW + HalfCW),(float)(cell.y * CellH + HalfCH) };
}

// 将世界坐标对齐到所属的单元格中心
inline void AlignWorld2Cell(Vector2Float &world)
{
	auto cpos = World2Cell(world);
	auto wpos = Cell2World(cpos);
	world = wpos;
}

// 方向值和游戏对象的素材索引有关联，不可随意
enum class Direction
{
	Up = 0,
	UpRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	UpLeft
};

enum class Horizontal
{
	None = -1,
	Left = 6,
	Right = 2
};

enum class Vertical
{
	None = -1,
	Up = 0,
	Down = 4
};
// 把8方向分解为水平和竖直方向上的描述
inline std::tuple<Horizontal, Vertical> DecomposeDir(Direction dir) 
{
	Horizontal x = Horizontal::None;
	Vertical y = Vertical::None;
	switch (dir)
	{
		case Direction::Up:
			y = Vertical::Up;
			break;
		case Direction::UpRight:
			x = Horizontal::Right;
			y = Vertical::Up;
			break;
		case Direction::Right:
			x = Horizontal::Right;
			break;
		case Direction::DownRight:
			x = Horizontal::Right;
			y = Vertical::Down;
			break;
		case Direction::Down:
			y = Vertical::Down;
			break;
		case Direction::DownLeft:
			x = Horizontal::Left;
			y = Vertical::Down;
			break;
		case Direction::Left:
			x = Horizontal::Left;
			break;
		case Direction::UpLeft:
			x = Horizontal::Left;
			y = Vertical::Up;
			break;
		default:
			break;
	}
	return std::tuple<Horizontal, Vertical>{x, y};
}