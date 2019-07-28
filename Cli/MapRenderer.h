#pragma once
#include "Map.h"
#include "MyGfx.h"

class MapRenderer
{
public:
	MapRenderer();
	~MapRenderer();
	void SetMap(Map *map);
	void SetPos(uint32_t x, uint32_t y);
	void Draw(float delta);
	void Scroll(Map::Horizontal x, Map::Vertical y);
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
	struct ScrollState
	{
		Map::Horizontal xType;
		Map::Vertical yType;
		int8_t xNeedScroll;
		int8_t yNeedScroll;
		float xScrolled;
		float yScrolled;
		int8_t xDir;
		int8_t yDir;
		float scrollSpeed;// ¹ö¶¯cellÊý/Ã¿Ãë

		void Set(Map::Horizontal x, Map::Vertical y);
		inline bool Update(float delta)
		{
			xScrolled += (xDir * CellW * scrollSpeed * delta);
			yScrolled += (yDir * CellH * scrollSpeed * delta);
			if ((xDir != 0 && abs(xScrolled) >= abs(xNeedScroll)) || (yDir != 0 && abs(yScrolled) >= abs(yNeedScroll))) {
				xNeedScroll == xScrolled; yNeedScroll == yScrolled;
				return false;
			}
			else
				return true;
		}
		inline void Reset()
		{
			xNeedScroll = 0; yNeedScroll = 0;
			xScrolled = 0; yScrolled = 0;
			xDir = 0; yDir = 0;
		}

		inline bool IsScrolling()
		{
			return (xNeedScroll != xScrolled) || (yNeedScroll != yScrolled);
		}
	};

	void CalcTileDrawState(uint16_t x, uint16_t y, DrawState & info);
	void CalcCellDrawState(DrawState & info);
	void DrawBG();
	void DrawMid();
	void DrawTop();
	void DrawDebugGrid();

	Map *mMap;
	uint32_t mX;
	uint32_t mY;
	DrawState mCellState;
	DrawState mTileState;
	ScrollState mScrollState;
};

