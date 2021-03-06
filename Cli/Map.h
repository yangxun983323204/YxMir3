#pragma once
#include <stdint.h>
#include <string>
#include "Common.h"

using std::string;
//=============================================
// Head
// TileInfo[w*h/4]   一个tile包含4个cell
// CellInfo[w*h]
//=============================================
#pragma pack(1)

struct MapLight
{
	int32_t IsLight;
	char LightSizeType;
	char LightColorType;
};

struct MapHeader
{
	char Desc[20];
	uint16_t Version;
	int16_t Width;// 宽高的单位是cell
	int16_t Height;
	char EventFileIndex;
	char FogColor;
};

struct TileInfo
{
	uint8_t FileIndex;
	uint16_t TileIndex;

	// 文件索引要做个变换，不知为何
	inline bool RemapFileIndex(int &idx) {
		ExFileIdx(idx);
		if ((idx % 14) > 2)
			return false;
		if (idx > 69)
			return false;

		return true;
	}
};

struct CellInfo
{
	uint8_t Flag;// 障碍层
	uint8_t Obj1Ani;
	uint8_t Obj2Ani;
	uint8_t FileIdx2;
	uint8_t FileIdx1;
	uint16_t Obj1;// 房屋及树的左半
	uint16_t Obj2;// 树的右半
	// DoorIndex & 0X80 for whether there is a door
	// DoorIndex & 0X7F for door index, if non-zero
	// DoorOffset & 0X80 for open/close the door
	// DoorOffset & 0X7F for door image offset
	uint16_t DoorIndex;
	uint8_t DoorOffset;
	uint16_t LightNEvent;

	inline uint32_t FileIndex1() { return FileIdx1 & 0x0f; }
	inline uint32_t FileIndex2() { return FileIdx2 & 0x0f; }
	inline bool File1Enable() { return FileIdx1 != 0xff && Obj1 != 65535 && Obj1>0 && Obj1<0x7fffffff; }
	inline bool File2Enable() { return FileIdx2 != 0xff && Obj2 != 65535 && Obj2>0 && Obj2<0x7fffffff; }
	inline bool HasAnim1() { return Obj1Ani != 255; }
	inline bool HasAnim2() { return Obj2Ani != 255; }
	inline bool Obj1Blend() { return Obj1Ani & 0x80 >> 7; }
	inline bool Obj2Blend() { return Obj2Ani & 0x80 >> 7; }
	inline unsigned char Obj1AnimTickType() { return Obj1Ani & 0x70 >> 4; }
	inline unsigned char Obj2AnimTickType() { return Obj2Ani & 0x70 >> 4; }
	inline short Obj1AnimCount() { return Obj1Ani & 0x0f; }
	inline short Obj2AnimCount() { return Obj2Ani & 0x0f; }
	inline bool HasDoor() { return (DoorOffset & 0x80) > 0 && (DoorIndex & 0x7f)>0; }
	inline uint32_t DoorImgIdx() { return DoorOffset & 0x7f; }
	inline bool Walkable() { return Flag & 0x01 ? true : false; }
	// ext
	inline uint32_t FileIndexOf(uint8_t idx) {
		if (idx == 1)
			return FileIndex1();
		else if (idx == 2)
			return FileIndex2();
		else
			return 0;
	}
	inline uint32_t ImgIndexOf(uint8_t idx) {
		if (idx == 1)
			return Obj1;
		else if (idx == 2)
			return Obj2;
		else
			return 0;
	}
	inline bool FileEnableOf(uint8_t idx) {
		if (idx == 1)
			return File1Enable();
		else if (idx == 2)
			return File2Enable();
		else
			return false;
	}
	inline bool HasAnimOf(uint8_t idx) {
		if (idx == 1)
			return HasAnim1();
		else if (idx == 2)
			return HasAnim2();
		else
			return false;
	}
	inline bool ObjBlendOf(uint8_t idx) {
		if (idx == 1)
			return Obj1Blend();
		else if (idx == 2)
			return Obj2Blend();
		else
			return false;
	}
	inline unsigned char AnimTickTypeOf(uint8_t idx) {
		if (idx == 1)
			return Obj1AnimTickType();
		else if (idx == 2)
			return Obj2AnimTickType();
		else
			return 0;
	}
	inline short AnimCountOf(uint8_t idx) {
		if (idx == 1)
			return Obj1AnimCount();
		else if (idx == 2)
			return Obj2AnimCount();
		else
			return 0;
	}
};

struct DoorImageInfo
{
	uint16_t PosX;
	uint16_t PosY;
	uint16_t ImageNum;
};

struct DoorInfo {
	uint8_t Index;
	uint8_t ImageCount;
	DoorImageInfo* ImageInfo;
};

#pragma pack()

class Map
{
public:
	Map();
	~Map();
	void Load(string mapPath);
	int16_t w();
	int16_t h();
	TileInfo TileAt(uint32_t cellX, uint32_t cellY);
	CellInfo CellAt(uint32_t x, uint32_t y);
	bool InMap(uint32_t cellX, uint32_t cellY);
	bool Walkable(uint32_t cellX, uint32_t cellY);
	bool NextWalkable(uint32_t cellX, uint32_t cellY,Direction dir);
	bool Next2Walkable(uint32_t cellX, uint32_t cellY, Direction dir);
private:
	void Clear();
	bool NextNWalkable(uint32_t x, uint32_t y, Direction dir,int n);
	string mPath;
	MapHeader *mHeader;
	TileInfo *mTiles;
	CellInfo *mCells;
	unsigned char mDoorCount;
	DoorInfo *mDoors;
	uint8_t *mCellDoorIndices;
	uint32_t mTileCount;
	uint32_t mCellCount;
};

