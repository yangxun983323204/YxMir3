#pragma once
#include <stdint.h>
#include <math.h>

// 为了让角色居中，因此让屏幕水平和竖直方向都显示奇数个格子
#define CellW 48
#define CellH 32
#define XCount 17
#define YCount 17
#define LayoutW  CellW*XCount
#define LayoutH  CellH*YCount
#define PI 3.1415926f
#define Rad2Deg (360 / (PI * 2))

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