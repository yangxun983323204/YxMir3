#include "Map.h"



Map::Map()
{
	mHeader = nullptr;
	mTiles = nullptr;
	mCells = nullptr;
	mDoorCount = 0;
	mDoors = nullptr;
	mCellDoorIndices = nullptr;
}


Map::~Map()
{
}

void Map::Load(string mapPath)
{
	Clear();
	mPath = mapPath;
	auto f = fopen(mPath.c_str(), "rb");
	mHeader = new MapHeader();
	fread(reinterpret_cast<void*>(mHeader), sizeof(MapHeader), 1, f);
	mTiles = new TileInfo[mHeader->Width*mHeader->Height/4];// 一个tile被分为田字形的4个cell
	mCells = new CellInfo[mHeader->Width*mHeader->Height];
	fread(reinterpret_cast<void*>(mTiles), sizeof(TileInfo), mHeader->Width*mHeader->Height / 4, f);
	fread(reinterpret_cast<void*>(mCells), sizeof(CellInfo), mHeader->Width*mHeader->Height, f);
	fread(reinterpret_cast<void*>(&mDoorCount), sizeof(unsigned char), 1, f);
	if (mDoorCount<=0)
		return;
	mDoors = new DoorInfo[mDoorCount];
	for (size_t i = 0; i < mDoorCount; i++)
	{
		auto door = mDoors[i];
		fread(reinterpret_cast<void*>(&door), sizeof(DoorInfo), 1, f);
		door.ImageInfo = new DoorImageInfo[door.ImageCount];
		for (size_t j = 0; j < door.ImageCount; j++)
		{
			fread(reinterpret_cast<void*>(&door.ImageInfo[i]), sizeof(DoorImageInfo), 1, f);
		}
	}
	// todo 此处可优化存储，考虑用稀疏矩阵什么的
	// 这段代码说明，一个门的范围可以大于一个cell
	mCellDoorIndices = new uint8_t[mHeader->Width*mHeader->Height];
	memset(reinterpret_cast<void*>(mCellDoorIndices), 0, sizeof(uint8_t)*mHeader->Width*mHeader->Height);
	for (size_t i = 0; i < mDoorCount; i++)
	{
		auto door = mDoors[i];
		for (size_t j = 0; j < mDoors[i].ImageCount; j++)
		{
			auto imgInfo = door.ImageInfo[j];
			mCellDoorIndices[imgInfo.PosX + imgInfo.PosY * mHeader->Width] = door.Index;
		}
	}
	fclose(f);
}

int16_t Map::w()
{
	if (mHeader != nullptr)
		return mHeader->Width;
	else
		return -1;
}

int16_t Map::h()
{
	if (mHeader != nullptr)
		return mHeader->Height;
	else
		return -1;
}

TileInfo Map::TileAt(uint32_t x, uint32_t y)
{
	return mTiles[y/2+(x/2)*mHeader->Height/2];
}

CellInfo Map::CellAt(uint32_t x, uint32_t y)
{
	return mCells[y + x*mHeader->Height];
}

void Map::Clear()
{
}
