#include "MapRenderer.h"
#include "WILIndex.h"
#include "SpriteMgr.h"

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
		yNeedScroll = -CellH;
	}
	else if (y == Map::Vertical::Up) {
		yDir = 1;
		yNeedScroll = CellH;
	}
	xType = x;
	yType = y;
}

MapRenderer::MapRenderer()
{
	mDebug = false;
	mScrollState.scrollSpeed = 2.0f;
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
			SetPos(mX - mScrollState.xDir, mY - mScrollState.yDir);
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
	uint8_t ext = 2;
	// 默认屏幕可以容纳17*17个cell,也就是可以容纳8.5*8.5个tile

	int cX = ceil(XCount / 2.0f) + ext * 2;
	int cY = ceil(YCount / 2.0f) + ext * 2;

	if (x % 2 ==0)
	{
		info.OffsetX = -CellW;
		info.MinX = -ceil(cX / 2.0f);
		info.MaxX = floor(cX / 2.0f);
	}
	else {
		info.OffsetX = 0;// -CellW;
		info.MinX = -floor(cX / 2.0f);
		info.MaxX = ceil(cX / 2.0f);
	}
	if (y % 2 == 0)
	{
		info.OffsetY = -CellH;
		info.MinY = -ceil(cY / 2.0f);
		info.MaxY = floor(cY / 2.0f);
	}
	else {
		info.OffsetY = 0;// -CellH;
		info.MinY = -floor(cY / 2.0f);
		info.MaxY = ceil(cY / 2.0f);
	}
	
	info.OffsetX -= ext*CellW;
	info.OffsetY -= ext*CellH;
}
void MapRenderer::CalcCellDrawState(DrawState &info)
{
	uint8_t ext = 36;// 上下左右均扩大ext的绘制范围，因为有些物体比较大
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
	auto sMgr = SpriteMgr::Instance();
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
			auto sprite = sMgr->GetSprite(fileIdx, tile.TileIndex);
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
	auto sMgr = SpriteMgr::Instance();
	int fileIdx;
	int imgIdx;
	bool blend;
	int drawX, drawY;
	MyGfx::Layer layers[2]{ MyGfx::Layer::Mid , MyGfx::Layer::Top};
	for (int x = -mCellState.MinX; x < mCellState.MaxX; ++x)
	{
		for (int y = -mCellState.MinY; y < mCellState.MaxY; ++y)
		{
			if (!mMap->InMap(x+mX, y+mY))
				continue;
			auto cell = mMap->CellAt(x+mX, y+mY);
			for (uint8_t i = 1; i < 3; i++)// 依次绘制中层和上层
			{
				if (cell.FileEnableOf(i))
				{
					fileIdx = cell.FileIndexOf(i);
					imgIdx = cell.ImgIndexOf(i);
					blend = false;
					if (fileIdx > 2 && fileIdx < 14) {
						if (cell.HasDoor())
							imgIdx += cell.DoorImgIdx();
						if (cell.HasAnimOf(i))
						{
							if (cell.ObjBlendOf(i))
								blend = true;
							//imgIdx += mMap->mAnimTileFrame[cell.Obj1AnimTickType()][cell.Obj1AnimCount()];// todo
						}
						auto sprite = sMgr->GetSprite(fileIdx, imgIdx);// todo 此步骤耗时严重，从70多帧降到11帧，看来资源管理要单独弄模块
						if (sprite != nullptr/* && sprite->w() == CellW && sprite->h() >= CellH*/) {
							// 地表物体图片的原点是左下角，因此注意这里绘制坐标中的y减去了图片高度
							drawX = (x + mCellState.OffsetX)*CellW + mScrollState.xScrolled;
							drawY = (y + mCellState.OffsetY)*CellH - sprite->h() + mScrollState.yScrolled;
							gfx->DrawCommand(sprite, drawX, drawY, layers[i]);
						}
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
