#pragma once
#include "WILIndex.h"
#include "ImageLib.h"
#include "MyGfx.h"
#include "Map.h"

using std::map;

class SpriteMgr
{
public:
	SpriteMgr();
	~SpriteMgr();
	// 是否是主要资源的管理器，不做成单例，ui精灵的是分开管理的
	bool IsMain() { return _isMain; }
	void InitMainLibs();
	// 手动初始化wil信息，主管理器不支持此方法
	bool ManulInitLibs(uint32_t fileIdx,std::string filePath);
	Sprite *GetSprite(uint32_t fileIdx,uint32_t imgIdx);
	// 有些影子是用原图变换出来的，并无直接素材
	Sprite *GetShadow(Sprite *base);
	Sprite *GetBuiltinSprite(uint8_t idx);
	ImageLib* GetLib(uint32_t idx) { return &mLibs[idx]; }

	static SpriteMgr *Main();
	
	const static uint8_t IdxBuiltinCross;
	const static uint8_t IdxBuiltinVLine;
private:
	bool _isMain;
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