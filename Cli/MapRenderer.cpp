#include "MapRenderer.h"
#include "WILIndex.h"

MapRenderer::MapRenderer()
{
	mDebug = false;
	mScrollDeltaX = 0;
	mScrollDeltaY = 0;
}


MapRenderer::~MapRenderer()
{
}

void MapRenderer::SetMap(Map * map)
{
	mMap = map;
}

void MapRenderer::Draw(uint32_t x, uint32_t y)
{
	mX = x;
	mY = y;
	CalcTileDrawState(mX, mY, mTileState);
	DrawBG();
	DrawMid();
	DrawTop();
	if (mDebug)
		DrawDebugGrid();
}

void MapRenderer::CalcTileDrawState(uint16_t x, uint16_t y, TileDrawInfo &info)
{
	// Ĭ����Ļ��������17*17��cell,Ҳ���ǿ�������8.5*8.5��tile
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

void MapRenderer::DrawBG()
{
	auto gfx = MyGfx::Instance();
	// ��Ļ��������17*17��cell,Ҳ���ǿ�������8.5*8.5��tile
	for (int x = mTileState.MinX; x < mTileState.MaxX; x++)
	{
		for (int y = mTileState.MinY; y < mTileState.MaxY; y++)
		{
			int cx = x * 2 + mX;// һ��tile��������2��cell�����cell����Ҫ����2
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
					(x-mTileState.MinX) * 96 + mTileState.OffsetX+ mScrollDeltaX, 
					(y-mTileState.MinY) * 64 + mTileState.OffsetY+ mScrollDeltaY, 
					MyGfx::Layer::Bottom
				);
		}
	}
}

void MapRenderer::DrawMid()
{
	// todo �߼��е�����
	auto gfx = MyGfx::Instance();
	int fileIdx;
	int imgIdx;
	bool blend;
	uint8_t ext = 10;// ������Ʒ�Χ����Ϊ��Щ����Ƚϴ�
	int offsetMin = floor(ext / 2.0f);
	int offsetMax = ceil(ext / 2.0f);
	for (int x = -offsetMin; x < offsetMax; x++)
	{
		for (int y = -offsetMin; y < offsetMax; y++)
		{
			if (!mMap->InMap(x+mX, y+mY))
				continue;
			auto cell = mMap->CellAt(x+mX, y+mY);
			
			if (cell.Obj1 != 65535)// �����в�
			{
				fileIdx = cell.FileIndex1;
				imgIdx = cell.Obj1;
				blend = false;
				if (fileIdx>2 && fileIdx<14)
				{
					//imgIdx += mMap->GetDoorImgIdx(x, y); // todo
					if (cell.HasAnim1())
					{
						if (cell.Obj1Blend())
							blend = true;
						//imgIdx += mMap->mAnimTileFrame[cell.Obj1AnimTickType()][cell.Obj1AnimCount()];// todo
					}
					auto sprite = gfx->GetSprite(WilList[fileIdx], imgIdx);
					gfx->DrawCommand(sprite, (x+ offsetMin)*CellW, (y+ offsetMin)*CellH, MyGfx::Layer::Mid);
				}
			}
			if (cell.Obj2 != 65535)// �����ϲ�
			{

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
