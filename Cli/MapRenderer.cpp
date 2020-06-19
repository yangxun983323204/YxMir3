#include "MapRenderer.h"
#include "WILIndex.h"
#include "SpriteMgr.h"

MapRenderer::MapRenderer()
{
	mDebug = false;
	mRedrawBG = true;
	//mScrollState.scrollSpeed = 4/1000.0f;
	//mScrollState.Reset();
	mTileState = { 0,0,0,0 };
	mCellState = { 0,0,0,0 };
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::SetMap(Map * map)
{
	mMap = map;
}

void MapRenderer::SetViewPoint(Vector2Float pos)
{
	mPos = pos;
	mRedrawBG = true;
	CalcTileDrawRect();
	CalcCellDrawRect();
}

void MapRenderer::SetViewPointDelta(Vector2Float pos)
{
	mPos.x += pos.x;
	mPos.y += pos.y;
	SetViewPoint(mPos);
}

Vector2Float MapRenderer::GetViewPoint()
{
	return mPos;
}

Vector2Float MapRenderer::GetPos()
{
	return mPos;
}

//Vector2Float MapRenderer::GetCellScrollOffset()
//{
//	return Vector2Float{ mScrollState.xScrolled, mScrollState.yScrolled };
//}

void MapRenderer::Draw(uint32_t delta)
{
	//if (mScrollState.IsScrolling()) {
	//	mRedrawBG = true;
	//	if (!mScrollState.Update(delta))// 如果返回false，说明滚动结束
	//	{
	//		SetPos(Vector2Float{ mPos.x - mScrollState.xDir*mScrollState.count, mPos.y - mScrollState.yDir*mScrollState.count });
	//	}
	//}
	DrawBG();
	DrawMid();
	DrawTop();
	if (mDebug)
		DrawDebugGrid();
}
//void MapRenderer::SetScrollSpeed(float cellPerSec)
//{
//	mScrollState.scrollSpeed = cellPerSec;
//}
//void MapRenderer::Scroll(Direction dir,uint8_t count)
//{
//	Horizontal x = Horizontal::None;
//	Vertical y = Vertical::None;
//	switch (dir)
//	{
//	case Direction::Up:
//		y = Vertical::Up;
//		break;
//	case Direction::UpRight:
//		x = Horizontal::Right;
//		y = Vertical::Up;
//		break;
//	case Direction::Right:
//		x = Horizontal::Right;
//		break;
//	case Direction::DownRight:
//		x = Horizontal::Right;
//		y = Vertical::Down;
//		break;
//	case Direction::Down:
//		y = Vertical::Down;
//		break;
//	case Direction::DownLeft:
//		x = Horizontal::Left;
//		y = Vertical::Down;
//		break;
//	case Direction::Left:
//		x = Horizontal::Left;
//		break;
//	case Direction::UpLeft:
//		x = Horizontal::Left;
//		y = Vertical::Up;
//		break;
//	default:
//		break;
//	}
//	Scroll(x, y, count);
//}
//void MapRenderer::Scroll(Horizontal x, Vertical y, uint8_t count)
//{
//	if(!mScrollState.IsScrolling())
//		mScrollState.Set(x, y, count);
//}

void MapRenderer::CalcTileDrawRect()
{
	uint8_t ext = 2;
	int halfX = floor(CellCountX / CellPerTileX / 2);
	int halfY = floor(CellCountY / CellPerTileX / 2);
	int posXLeft = floor(mPos.x);
	int posYLeft = floor(mPos.y);
	int posXRight = ceil(mPos.x);
	int posYRight = ceil(mPos.y);

	mTileState.MinCellX = posXLeft / TileW - halfX - ext;
	mTileState.MaxCellX = posXRight / TileW + halfX + ext;
	mTileState.MinCellY = posYLeft / TileH - halfY - ext;
	mTileState.MaxCellY = posYRight / TileH + halfY + ext;
}
void MapRenderer::CalcCellDrawRect()
{
	uint8_t ext = 36;// 上下左右均扩大ext的绘制范围，因为有些物体比较大
	int halfX = floor(CellCountX / 2);
	int halfY = floor(CellCountY / 2);
	int posXLeft = floor(mPos.x);
	int posYLeft = floor(mPos.y);
	int posXRight = ceil(mPos.x);
	int posYRight = ceil(mPos.y);

	mCellState.MinCellX = posXLeft / CellW - halfX - ext;
	mCellState.MaxCellX = posXRight / CellW + halfX + ext;
	mCellState.MinCellY = posYLeft / CellH - halfY - ext;
	mCellState.MaxCellY = posYRight / CellH + halfY + ext;
}
void MapRenderer::DrawBG()
{
	if (!mRedrawBG)
		return;
	//mRedrawBG = false;
	auto gfx = MyGfx::Instance();
	auto sMgr = SpriteMgr::Main();
	for (int x = mTileState.MinCellX; x <= mTileState.MaxCellX; x++)
	{
		for (int y = mTileState.MinCellY; y <= mTileState.MaxCellY; y++)
		{
			int cx = x * CellPerTileX;// 一个tile横竖都是2个cell，因此cell坐标要乘以2
			int cy = y * CellPerTileY;
			if (cx<0 || cy <0 || !mMap->InMap(cx, cy))
				continue;
			auto tile = mMap->TileAt(cx, cy);
			int fileIdx = tile.FileIndex;
			if (!tile.RemapFileIndex(fileIdx))
				continue;

			auto sprite = sMgr->GetSprite(fileIdx, tile.TileIndex);
			if (sprite)
				sprite->PivotX = 0;
				sprite->PivotY = 0;
				gfx->DrawCommand(sprite, x * TileW,y * TileH,MyGfx::Layer::Bottom);
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
	for (int x = mCellState.MinCellX; x <= mCellState.MaxCellX; ++x)
	{
		for (int y = mCellState.MinCellY; y <= mCellState.MaxCellY; ++y)
		{
			if (x<0 || y<0 || !mMap->InMap(x, y))
				continue;
			auto cell = mMap->CellAt(x, y);
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
							drawX = x*CellW;
							drawY = y*CellH - sprite->h();
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
