#include "MapRenderer.h"
#include "WILIndex.h"

void MapRenderer::ScrollState::Set(Map::Horizontal x, Map::Vertical y)
{
	Reset();
	if (x == Map::Horizontal::Right) {
		xDir = -1;
		xNeedScroll = -CellW;
	}
	else if (x == Map::Horizontal::Left) {
		xDir = 1;
		xNeedScroll = CellW;
	}

	if (y == Map::Vertical::Down) {
		yDir = -1;
		yNeedScroll = -CellW;
	}
	else if (y == Map::Vertical::Up) {
		yDir = 1;
		yNeedScroll = CellW;
	}
	xType = x;
	yType = y;
}

MapRenderer::MapRenderer()
{
	mDebug = false;
	mScrollState.scrollSpeed = 1.0f;
	mScrollState.Reset();
	CalcCellDrawState(mCellState);
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::SetMap(Map * map)
{
	mMap = map;
}

void MapRenderer::SetPos(uint32_t x, uint32_t y)
{
	mX = x;
	mY = y;
	mScrollState.Reset();
	CalcTileDrawState(mX, mY, mTileState);
}

void MapRenderer::Draw(float delta)
{
	if (mScrollState.IsScrolling()) {
		if (!mScrollState.Update(delta))// 如果返回false，说明滚动结束
		{
			mX -= mScrollState.xDir;
			mY -= mScrollState.yDir;
			mScrollState.Reset();
		}
	}
	DrawBG();
	DrawMid();
	DrawTop();
	if (mDebug)
		DrawDebugGrid();
}

void MapRenderer::Scroll(Map::Horizontal x, Map::Vertical y)
{
	if(!mScrollState.IsScrolling())
		mScrollState.Set(x, y);
}

void MapRenderer::CalcTileDrawState(uint16_t x, uint16_t y, DrawState &info)
{
	// 默认屏幕可以容纳17*17个cell,也就是可以容纳8.5*8.5个tile
	float cX = XCount / 2.0f;
	float cY = YCount / 2.0f;
	if (x % 2 ==0)
	{
		info.OffsetX = -CellW;
		info.MinX = -ceil(cX / 2);
		info.MaxX = floor(cX / 2);
	}
	else {
		info.OffsetX = CellW;
		info.MinX = -floor(cX / 2);
		info.MaxX = ceil(cX / 2);
	}
	if (y % 2 == 0)
	{
		info.OffsetY = -CellH;
		info.MinY = -ceil(cY / 2);
		info.MaxY = floor(cY / 2);
	}
	else {
		info.OffsetX = CellH;
		info.MinY = -floor(cY / 2);
		info.MaxY = ceil(cY / 2);
	}
}
void MapRenderer::CalcCellDrawState(DrawState &info)
{
	uint8_t ext = 16;// 上下左右均扩大ext的绘制范围，因为有些物体比较大
	info.MinX = floor((ext * 2 + XCount) / 2.0f);
	info.MaxX = ceil((ext * 2 + XCount) / 2.0f);
	info.MinY = floor((ext * 2 + YCount) / 2.0f);
	info.MaxY = ceil((ext * 2 + YCount) / 2.0f);
	info.OffsetX = floor(XCount / 2.0f);
	info.OffsetY = floor(YCount / 2.0f);
}
void MapRenderer::DrawBG()
{
	auto gfx = MyGfx::Instance();
	// 屏幕可以容纳17*17个cell,也就是可以容纳8.5*8.5个tile
	for (int x = mTileState.MinX; x < mTileState.MaxX; x++)
	{
		for (int y = mTileState.MinY; y < mTileState.MaxY; y++)
		{
			int cx = x * 2 + mX;// 一个tile横竖都是2个cell，因此cell坐标要乘以2
			int cy = y * 2 + mY;
			if (!mMap->InMap(cx, cy))
				continue;
			auto tile = mMap->TileAt(cx, cy);
			int fileIdx = tile.FileIndex;
			ImageLib::ExFileIdx(fileIdx);
			if ((fileIdx % 14) > 2)
				continue;
			if (fileIdx > 69)
				continue;
			auto filePath = WilList[fileIdx];
			auto sprite = gfx->GetSprite(filePath, tile.TileIndex);
			if (sprite)
				gfx->DrawCommand(
					sprite, 
					(x-mTileState.MinX) * 96 + mTileState.OffsetX+ mScrollState.xScrolled,
					(y-mTileState.MinY) * 64 + mTileState.OffsetY+ mScrollState.yScrolled,
					MyGfx::Layer::Bottom
				);
		}
	}
}

void MapRenderer::DrawMid()
{
	auto gfx = MyGfx::Instance();
	int fileIdx;
	int imgIdx;
	bool blend;
	for (int x = -mCellState.MinX; x < mCellState.MaxX; x++)
	{
		for (int y = -mCellState.MinY; y < mCellState.MaxY; y++)
		{
			if (!mMap->InMap(x+mX, y+mY))
				continue;
			auto cell = mMap->CellAt(x+mX, y+mY);
			
			if (cell.File1Enable())// 绘制中层
			{
				fileIdx = cell.FileIndex1();
				imgIdx = cell.Obj1;
				blend = false;
				if (fileIdx>2 && fileIdx<14)
				{
					if (cell.HasDoor())
						imgIdx += cell.DoorImgIdx();
					if (cell.HasAnim1())
					{
						if (cell.Obj1Blend())
							blend = true;
						//imgIdx += mMap->mAnimTileFrame[cell.Obj1AnimTickType()][cell.Obj1AnimCount()];// todo
					}
					auto sprite = gfx->GetSprite(WilList[fileIdx], imgIdx);
					if (sprite != nullptr/* && sprite->w() == CellW && sprite->h() >= CellH*/) {
						// 地表物体图片的原点是左下角，因此注意这里绘制坐标中的y减去了图片高度
						gfx->DrawCommand(sprite, (x + mCellState.OffsetX)*CellW+mScrollState.xScrolled, (y + mCellState.OffsetY)*CellH - sprite->h()+mScrollState.yScrolled, MyGfx::Layer::Mid);
					}
				}
			}
			if (cell.File2Enable())// 绘制上层
			{
				fileIdx = cell.FileIndex2();
				imgIdx = cell.Obj2;
				blend = false;
				if (fileIdx>2 && fileIdx<14)
				{
					if (cell.HasDoor())
						imgIdx += cell.DoorImgIdx();
					if (cell.HasAnim2())
					{
						if (cell.Obj2Blend())
							blend = true;
						//imgIdx += mMap->mAnimTileFrame[cell.Obj1AnimTickType()][cell.Obj1AnimCount()];// todo
					}
					auto sprite = gfx->GetSprite(WilList[fileIdx], imgIdx);
					if (sprite != nullptr/* && sprite->w() == CellW && sprite->h() >= CellH*/) {
						// 地表物体图片的原点是左下角，因此注意这里绘制坐标中的y减去了图片高度
						gfx->DrawCommand(sprite, (x + mCellState.OffsetX)*CellW + mScrollState.xScrolled, (y + mCellState.OffsetY)*CellH - sprite->h() + mScrollState.yScrolled, MyGfx::Layer::Mid);
					}
				}
			}
		}
	}
}

void MapRenderer::DrawTop()
{
	
}

void MapRenderer::DrawDebugGrid()
{
}
