#include "MapRenderer.h"
#include "WILIndex.h"
#include "SpriteMgr.h"

MapRenderer::MapRenderer()
{
	mDebug = false;
	mRedrawBG = true;
	mScrollState.scrollSpeed = 4/1000.0f;
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

void MapRenderer::SetPos(Vector2UInt pos)
{
	mPos = pos;
	mScrollState.Reset();
	CalcTileDrawState(mPos.x, mPos.y, mTileState);
}

Vector2UInt MapRenderer::GetPos()
{
	return mPos;
}

Vector2Float MapRenderer::GetCellScrollOffset()
{
	return Vector2Float{ mScrollState.xScrolled, mScrollState.yScrolled };
}

void MapRenderer::Draw(uint32_t delta)
{
	if (mScrollState.IsScrolling()) {
		mRedrawBG = true;
		if (!mScrollState.Update(delta))// 如果返回false，说明滚动结束
		{
			SetPos(Vector2UInt{ mPos.x - mScrollState.xDir*mScrollState.count, mPos.y - mScrollState.yDir*mScrollState.count });
		}
	}
	DrawBG();
	DrawMid();
	DrawTop();
	if (mDebug)
		DrawDebugGrid();
}
void MapRenderer::SetScrollSpeed(float cellPerSec)
{
	mScrollState.scrollSpeed = cellPerSec;
}
void MapRenderer::Scroll(Direction dir,uint8_t count)
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
	Scroll(x, y, count);
}
void MapRenderer::Scroll(Horizontal x, Vertical y, uint8_t count)
{
	if(!mScrollState.IsScrolling())
		mScrollState.Set(x, y, count);
}

void MapRenderer::CalcTileDrawState(uint16_t x, uint16_t y, DrawState &info)
{
	uint8_t ext = 2;
	// 默认屏幕可以容纳17*17个cell,也就是可以容纳8.5*8.5个tile

	int cX = floor(XCount / 2.0f);
	int cY = floor(YCount / 2.0f);

	if (x % 2 !=0)
	{
		info.OffsetX = -CellW*2;
		info.MinX = -ceil(cX / 2.0f);
		info.MaxX = floor(cX / 2.0f);
	}
	else {
		info.OffsetX = -CellW;
		info.MinX = -floor(cX / 2.0f);
		info.MaxX = ceil(cX / 2.0f);
	}
	if (y % 2 != 0)
	{
		info.OffsetY = -CellH*2;
		info.MinY = -ceil(cY / 2.0f);
		info.MaxY = floor(cY / 2.0f);
	}
	else {
		info.OffsetY = -CellH;
		info.MinY = -floor(cY / 2.0f);
		info.MaxY = ceil(cY / 2.0f);
	}
	info.OffsetX += (-info.MinX+0.5f)*96;
	info.OffsetY += (-info.MinY+0.5f)*64;
	info.MinX -= ext;
	info.MaxX += ext;
	info.MinY -= ext;
	info.MaxY += ext;
}
void MapRenderer::CalcCellDrawState(DrawState &info)
{
	uint8_t ext = 36;// 上下左右均扩大ext的绘制范围，因为有些物体比较大
	info.MinX = -(floor(XCount / 2.0f)+ext);
	info.MaxX = ceil(XCount / 2.0f)+ext;
	info.MinY = -(floor(YCount / 2.0f)+ext);
	info.MaxY = ceil(YCount / 2.0f)+ext;
	info.OffsetX = floor(XCount / 2.0f);
	info.OffsetY = ceil(YCount / 2.0f);
}
void MapRenderer::DrawBG()
{
	if (!mRedrawBG)
		return;
	mRedrawBG = false;
	auto gfx = MyGfx::Instance();
	auto sMgr = SpriteMgr::Main();
	// 屏幕可以容纳17*17个cell,也就是可以容纳8.5*8.5个tile
	for (int x = mTileState.MinX; x <= mTileState.MaxX; x++)
	{
		for (int y = mTileState.MinY; y <= mTileState.MaxY; y++)
		{
			int cx = x * 2 + mPos.x;// 一个tile横竖都是2个cell，因此cell坐标要乘以2
			int cy = y * 2 + mPos.y;
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
				sprite->PivotX = 0;
				sprite->PivotY = 0;
				gfx->DrawCommand(
					sprite, 
					x * 96 + mTileState.OffsetX + mScrollState.xScrolled,
					y * 64 + mTileState.OffsetY + mScrollState.yScrolled,
					MyGfx::Layer::Bottom
				);
		}
	}
}

void MapRenderer::DrawMid()
{
	auto gfx = MyGfx::Instance();
	auto sMgr = SpriteMgr::Main();
	int fileIdx;
	int imgIdx;
	bool blend;
	int drawX, drawY;
	for (int x = mCellState.MinX; x <= mCellState.MaxX; ++x)
	{
		for (int y = mCellState.MinY; y <= mCellState.MaxY; ++y)
		{
			if (!mMap->InMap(x+mPos.x, y+mPos.y))
				continue;
			auto cell = mMap->CellAt(x+ mPos.x, y+ mPos.y);
			for (uint8_t i = 1; i < 3; i++)// 依次绘制左侧和右侧
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
						auto sprite = sMgr->GetSprite(fileIdx, imgIdx);
						if (sprite != nullptr) {
							sprite->PivotX = 0;
							sprite->PivotY = 0;
							// 地表物体图片的原点是左下角，因此注意这里绘制坐标中的y减去了图片高度
							drawX = (x + mCellState.OffsetX)*CellW + mScrollState.xScrolled;
							drawY = (y + mCellState.OffsetY)*CellH - sprite->h() + mScrollState.yScrolled;
							gfx->DrawCommand(sprite, drawX, drawY, MyGfx::Layer::Mid);
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
