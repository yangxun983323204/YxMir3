#pragma once
#include "SDLInc.h"
#include "ImageLib.h"
#include <map>
#include <vector>
#include "Delegate.hpp"

using Yx::Delegate;

class Sprite
{
	friend class SpriteMgr;
public:
	enum class ShadowType 
	{
		Orth,
		Proj,
	};
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
		_shadow = nullptr;
		_shadowType = ShadowType::Proj;
	}
	~Sprite()
	{
		SDL_FreeSurface(Surface);
		if (_shadow != nullptr) {
			delete _shadow;
			_shadow = nullptr;
		}
	}

	inline uint16_t w()
	{
		return OverridW == 0 ? Surface->w : OverridW;
	}
	inline uint16_t h()
	{
		return OverridH == 0 ? Surface->h : OverridH;
	}
private:
	Sprite* _shadow;
	ShadowType _shadowType;
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

struct TempDrawInfo :public DrawInfo{
	~TempDrawInfo()
	{
		delete sprite;
		sprite = nullptr;
	}
};

enum BlendType// ?
{
	Normal = 0,
	Light,
	LightInv,
	InvNormal,
	InvLight,
	InvLightInv,
};

class MyGfx
{
public:
	enum Layer
	{
		Bottom,
		Mid,
		Top,
		GUI,
	};

	MyGfx(std::wstring title,uint16_t w,uint16_t h);
	~MyGfx();

	const SDL_Rect *GetRenderRect();
	void SetFPS(uint16_t requireFPS);
	void Resize(uint16_t w, uint16_t h);
	void DrawString(std::wstring str,int x,int y);
	void DrawCommand(Sprite * sprite, int x, int y, Layer layer);
	void DrawCommand(Sprite * sprite, int x, int y,int w,int h, Layer layer);
	void DrawCache();
	void RunLoop();
	void Exit();

	static Sprite* CreateSpriteFromImage(Image *image);
	static inline void MyGfx::GetDrawRect(DrawInfo *info,bool useOffset, __out SDL_Rect* srcRect, __out SDL_Rect* dstRect);
	static MyGfx *Instance();
	// 不管理生命周期
	static Sprite *CreateTextSprite(std::wstring str);

	Delegate<void(uint32_t deltaMs)> onDraw;
	Delegate<void(SDL_Event*)> onEvent;

	bool mDebug;

	static TTF_Font *gFont;
private:
	SDL_Window *mWindow;

	SDL_Rect mScreenRect;

	std::vector<DrawInfo> mMidCache;
	std::vector<DrawInfo> mTopCache;
	std::vector<DrawInfo> mGuiCache;
	SDL_Surface* mScreenSurface;
	SDL_Surface* mBgSurface;
	uint16_t mRequireFPS;
	uint16_t mFPS;

	bool mLoop;
	uint32_t mFrameTime;//ms
	uint32_t mCurrFrameTime;//ms

	static bool DrawInfoSort(const DrawInfo &a, const DrawInfo &b);
	static MyGfx *_inst;
};

