#pragma once
#include "Map.h"
#include "MyGfx.h"

class MapRenderer
{
public:
	MapRenderer();
	~MapRenderer();
	void SetMap(Map *map);
	void Draw(uint32_t x, uint32_t y);
	void Scroll(Map::Horizontal x, Map::Vertical y);

	bool mDebug;
private:
	struct TileDrawInfo
	{
		int OffsetX;
		int OffsetY;
		int MinX;
		int MinY;
		int MaxX;
		int MaxY;
	};

	void CalcTileDrawState(uint16_t x, uint16_t y, TileDrawInfo & info);
	void DrawBG();
	void DrawMid();
	void DrawTop();
	void DrawDebugGrid();

	Map *mMap;
	uint32_t mX;
	uint32_t mY;
	TileDrawInfo mTileState;
	int32_t mScrollDeltaX;
	int32_t mScrollDeltaY;
};

