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
	void SetViewPoint(Vector2Float pos);
	void SetViewPointDelta(Vector2Float pos);
	Vector2Float GetViewPoint();
	Vector2Float GetPos();
	void Draw(uint32_t delta);
	bool mDebug;
private:
	struct DrawRect
	{
		int MinCellX;
		int MinCellY;
		int MaxCellX;
		int MaxCellY;
	};

	void CalcTileDrawRect();
	void CalcCellDrawRect();
	void UpdateAnimTile(uint32_t delta);
	void DrawBG();
	void DrawMid();
	void DrawTop();
	void DrawDebugGrid();

	Map *mMap;
	Vector2Float mPos;
	DrawRect mCellState;
	DrawRect mTileState;
	uint32_t _animTileTime[8];
	uint8_t _animTileState[8][16];// 有8种帧速，0~15个动画帧图
	bool mRedrawBG;
};

