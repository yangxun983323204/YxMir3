#pragma once
#include <map>
#include "WILIndex.h"
#include "ImageLib.h"
#include "MyGfx.h"

using std::map;

class SpriteMgr
{
public:
	SpriteMgr();
	~SpriteMgr();

	void InitLibs();
	Sprite *GetSprite(uint32_t fileIdx,uint32_t imgIdx);

	static SpriteMgr *Instance();
private:
	void ClearCache();

	ImageLib mLibs[_MAX_IMAGE];
	map<uint32_t, Sprite*> mSpriteMap[_MAX_IMAGE];

	static SpriteMgr *_inst;
};