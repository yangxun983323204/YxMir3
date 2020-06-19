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
	//Vector2Float GetCellScrollOffset();
	void Draw(uint32_t delta);
	//void SetScrollSpeed(float cellPerSec);
	//void Scroll(Direction dir, uint8_t count=1);
	//void Scroll(Horizontal x, Vertical y, uint8_t count=1);
	/*void CompleteScroll() {
		mRedrawBG = true;
		mScrollState.CompleteIt();
		SetPos(Vector2Float{ mPos.x - mScrollState.xDir*mScrollState.count, mPos.y - mScrollState.yDir*mScrollState.count });
	}*/
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
	void DrawBG();
	void DrawMid();
	void DrawTop();
	void DrawDebugGrid();

	Map *mMap;
	Vector2Float mPos;
	DrawRect mCellState;
	DrawRect mTileState;
	//MoveState mScrollState;
	bool mRedrawBG;
};

