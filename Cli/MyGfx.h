#pragma once
#include "SDLInc.h"
#include "ImageLib.h"
#include <map>

class Sprite
{
public:
	int16_t PivotX;
	int16_t PivotY;
	bool HasShadow;
	int16_t ShadowPosX;
	int16_t ShadowPosY;
	SDL_Surface* Surface;
};

class MyGfx
{
public:

	

	MyGfx();
	~MyGfx();

	void Draw(Sprite* sprite);
	Sprite* GetSprite(string wixPath, string index);
	static Sprite* CreateSpriteFromImage(Image *image);
private:
	std::map<string, Sprite*> mEnvSprites;// 动态加载地图所用精灵
	std::map<string, Sprite*> mObjSprites;// 常驻其它精灵
};

