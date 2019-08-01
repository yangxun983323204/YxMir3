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
	mRedrawBG = true;
	mScrollState.scrollSpeed = 4.0f;
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
	mPos.x = x;
	mPos.y = y;
	mScrollState.Reset();
	CalcTileDrawState(x, y, mTileState);
}

Vector2UInt MapRenderer::GetPos()
{
	return mPos;
}

Vector2Float MapRenderer::GetCellScrollOffset()
{
	return Vector2Float{ mScrollState.xScrolled, mScrollState.yScrolled };
}

void MapRenderer::Draw(float delta)
{
	if (mScrollState.IsScrolling()) {
		mRedrawBG = true;
		if (!mScrollState.Update(delta))// �������false��˵����������
		{
			SetPos(mPos.x - mScrollState.xDir, mPos.y - mScrollState.yDir);
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
	// Ĭ����Ļ��������17*17��cell,Ҳ���ǿ�������8.5*8.5��tile

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
	info.OffsetX += (-info.MinX)*96;
	info.OffsetY += (-info.MinY)*64;
	info.MinX -= ext;
	info.MaxX += ext;
	info.MinY -= ext;
	info.MaxY += ext;
}
void MapRenderer::CalcCellDrawState(DrawState &info)
{
	uint8_t ext = 36;// �������Ҿ�����ext�Ļ��Ʒ�Χ����Ϊ��Щ����Ƚϴ�
	info.MinX = -(floor(XCount / 2.0f)+ext);
	info.MaxX = ceil(XCount / 2.0f)+ext;
	info.MinY = -(floor(YCount / 2.0f)+ext);
	info.MaxY = ceil(YCount / 2.0f)+ext;
	info.OffsetX = floor(XCount / 2.0f);
	info.OffsetY = floor(YCount / 2.0f);
}
void MapRenderer::DrawBG()
{
	if (!mRedrawBG)
		return;
	mRedrawBG = false;
	auto gfx = MyGfx::Instance();
	auto sMgr = SpriteMgr::Instance();
	// ��Ļ��������17*17��cell,Ҳ���ǿ�������8.5*8.5��tile
	for (int x = mTileState.MinX; x <= mTileState.MaxX; x++)
	{
		for (int y = mTileState.MinY; y <= mTileState.MaxY; y++)
		{
			int cx = x * 2 + mPos.x;// һ��tile��������2��cell�����cell����Ҫ����2
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
	auto sMgr = SpriteMgr::Instance();
	int fileIdx;
	int imgIdx;
	bool blend;
	int drawX, drawY;
	MyGfx::Layer layers[2]{ MyGfx::Layer::Mid , MyGfx::Layer::Top};
	for (int x = mCellState.MinX; x <= mCellState.MaxX; ++x)
	{
		for (int y = mCellState.MinY; y <= mCellState.MaxY; ++y)
		{
			if (!mMap->InMap(x+mPos.x, y+mPos.y))
				continue;
			auto cell = mMap->CellAt(x+ mPos.x, y+ mPos.y);
			for (uint8_t i = 1; i < 3; i++)// ���λ����в���ϲ�
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
							// �ر�����ͼƬ��ԭ�������½ǣ����ע��������������е�y��ȥ��ͼƬ�߶�
							drawX = (x + mCellState.OffsetX)*CellW + mScrollState.xScrolled;
							drawY = (y + mCellState.OffsetY)*CellH - sprite->h() + mScrollState.yScrolled;
							gfx->DrawCommand(sprite, drawX, drawY, layers[0]);
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
