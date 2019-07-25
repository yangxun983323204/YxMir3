#pragma once
#include <stdint.h>
#include <string>
using std::string;
//=============================================
// Head
// TileInfo[w*h/4]   一个tile包含4个cell
// CellInfo[w*h]
//=============================================


#pragma pack(1)

#define CellW = 48;
#define CellH = 32;

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
};

struct CellInfo
{
	uint8_t Flag;// 障碍层
	uint8_t Obj1Ani;
	uint8_t Obj2Ani;
	uint8_t FileIndex2;
	uint8_t FileIndex1;
	uint16_t Obj1;
	uint16_t Obj2;
	// DoorIndex & 0X80 for whether there is a door
	// DoorIndex & 0X7F for door index, if non-zero
	// DoorOffset & 0X80 for open/close the door
	// DoorOffset & 0X7F for door image offset
	uint16_t DoorIndex;
	uint8_t DoorOffset;
	uint16_t LightNEvent;
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
	TileInfo TileAt(uint32_t x, uint32_t y);
	CellInfo CellAt(uint32_t x, uint32_t y);
private:
	void Clear();

	string mPath;
	MapHeader *mHeader;
	TileInfo *mTiles;
	CellInfo *mCells;
	unsigned char mDoorCount;
	DoorInfo *mDoors;
	uint8_t *mCellDoorIndices;
};

