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
	uint16_t OverridW;
	uint16_t OverridH;

	Sprite() {
		PivotX = PivotY = ShadowPosX = ShadowPosY = OverridW = OverridH = 0;
		Surface = nullptr;
		HasShadow = false;
	}

	inline uint16_t w()
	{
		return OverridW == 0 ? Surface->w : OverridW;
	}
	inline uint16_t h()
	{
		return OverridH == 0 ? Surface->h : OverridH;
	}
};

struct DrawInfo
{
	Sprite *sprite;
	int16_t x;
	int16_t y;
	int16_t w;
	int16_t h;
	DrawInfo()
	{
		sprite = nullptr;
	}
	// 不能在析构释放精灵，因为是gfx在统一管理
};

class MyGfx
{
public:
	enum Layer
	{
		Bottom,
		Mid,
		Top,
	};

	MyGfx(std::string title,uint16_t w,uint16_t h);
	~MyGfx();

	void DrawCommand(Sprite * sprite, int x, int y, Layer layer);
	void DrawCache();
	Sprite* GetSprite(string wilPath, uint32_t index);
	static Sprite* CreateSpriteFromImage(Image *image);
	static inline void MyGfx::GetDrawRect(DrawInfo *info, __out SDL_Rect* srcRect, __out SDL_Rect* dstRect);
	static MyGfx *Instance();
private:
	SDL_Window *mWindow;
	std::map<string, Sprite*> mEnvSprites;// 动态加载地图所用精灵
	std::map<string, Sprite*> mObjSprites;// 常驻其它精灵

	std::vector<DrawInfo> mMidCache;
	std::vector<DrawInfo> mTopCache;
	SDL_Surface* mScreenSurface;
	SDL_Surface* mBgSurface;

	static bool DrawInfoSort(DrawInfo a, DrawInfo b);
	static MyGfx *_inst;
};

