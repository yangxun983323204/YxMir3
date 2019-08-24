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
	// 有些影子是用原图变换出来的，并无直接素材
	Sprite *GetShadow(Sprite *base,Sprite::ShadowType type);
	Sprite *GetBuiltinSprite(uint8_t idx);

	static SpriteMgr *Instance();
	
	const static uint8_t IdxBuiltinCross;
	const static uint8_t IdxBuiltinVLine;
private:
	SpriteMgr();

	struct LibImgCache
	{
		uint16_t size;
		Sprite** sprites;
	};

	Sprite* CreateOrthShadow(Sprite *base);
	Sprite* CreateProjShadow(Sprite *base);
	void ClearCache();

	ImageLib mLibs[_MAX_IMAGE];
	LibImgCache mSpriteMap[_MAX_IMAGE];

	static bool Inited;
	static uint16_t	BuiltinSpriteCount;
	static Sprite** BuiltinSprite;
	static void Init();

	static SpriteMgr *_inst;
};