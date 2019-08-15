#pragma once
#include "Map.h"
#include "MyGfx.h"
#include "Common.h"

class MapRenderer
{
public:
	MapRenderer();
	~MapRenderer();
	void SetMap(Map *map);
	void SetPos(uint32_t x, uint32_t y);
	Vector2UInt GetPos();
	Vector2Float GetCellScrollOffset();
	void Draw(float delta);
	void SetScrollSpeed(float cellPerSec);
	void Scroll(Direction dir);
	void Scroll(Horizontal x, Vertical y);
	bool mDebug;
private:
	struct DrawState
	{
		int OffsetX;
		int OffsetY;
		int MinX;
		int MinY;
		int MaxX;
		int MaxY;
	};

	void CalcTileDrawState(uint16_t x, uint16_t y, DrawState & info);
	void CalcCellDrawState(DrawState & info);
	void DrawBG();
	void DrawMid();
	void DrawTop();
	void DrawDebugGrid();

	Map *mMap;
	Vector2UInt mPos;
	DrawState mCellState;
	DrawState mTileState;
	ScrollState mScrollState;
	bool mRedrawBG;
};

