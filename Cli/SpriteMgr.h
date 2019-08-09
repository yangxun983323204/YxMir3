#pragma once
#include "WILIndex.h"
#include "ImageLib.h"
#include "MyGfx.h"
#include "Map.h"

using std::map;

class SpriteMgr
{
public:
	~SpriteMgr();

	void InitLibs();
	Sprite *GetSprite(uint32_t fileIdx,uint32_t imgIdx);
	Sprite *GetBuiltinSprite(uint8_t idx);

	static SpriteMgr *Instance();
	
	const static uint8_t IdxBuiltinCross;
private:
	SpriteMgr();

	struct LibImgCache
	{
		uint16_t size;
		Sprite** sprites;
	};

	void ClearCache();

	ImageLib mLibs[_MAX_IMAGE];
	LibImgCache mSpriteMap[_MAX_IMAGE];

	static bool Inited;
	static uint16_t	BuiltinSpriteCount;
	static Sprite** BuiltinSprite;
	static void Init();

	static SpriteMgr *_inst;
};