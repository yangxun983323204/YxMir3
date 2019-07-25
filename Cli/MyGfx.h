#pragma once
#include "SDLInc.h"
#include "ImageLib.h"
#include <map>
#include <vector>

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

struct DrawInfo
{
	Sprite *sprite;
	int16_t x;
	int16_t y;
	int16_t w;
	int16_t h;
};

class MyGfx
{
public:
	MyGfx(SDL_Window* window);
	~MyGfx();

	void DrawCommand(Sprite * sprite, int x, int y, int w = 0, int h = 0);
	void DrawCache();
	Sprite* GetSprite(string wilPath, uint32_t index);
	static Sprite* CreateSpriteFromImage(Image *image);
	static inline void MyGfx::GetDrawRect(DrawInfo *info, __out SDL_Rect* srcRect, __out SDL_Rect* dstRect);
private:
	SDL_Window *mWindow;
	std::map<string, Sprite*> mEnvSprites;// 动态加载地图所用精灵
	std::map<string, Sprite*> mObjSprites;// 常驻其它精灵

	std::vector<DrawInfo> mDrawCache;
	SDL_Surface* mScreenSurface;

	static bool DrawInfoSort(DrawInfo a, DrawInfo b);
};

