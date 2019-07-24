#pragma once
#include <stdint.h>

//=============================================
// Head
// TileInfo[]
// CellInfo[]
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
	uint16_t Attr;
	int16_t Width;// 宽高的单位是cell
	int16_t Height;
	char EventFileIndex;
	char FogColor;
};

struct TileInfo
{
	uint8_t FileIndex;
	uint8_t TileIndex;
};

struct CellInfo
{
	uint8_t Flag;
	uint8_t Obj1Ani;
	uint8_t Obj2Ani;
	uint8_t FileIndex2;
	uint8_t FileIndex1;
	uint16_t Obj1;
	uint16_t Obj2;
	uint16_t DoorIndex;
	uint8_t DoorOffset;
	uint16_t LightNEvent;
};

#pragma pack()

class Map
{
public:
	Map();
	~Map();
};

