#pragma once
#include "SDLInc.h"
#include "ImageLib.h"
#include <map>
#include <vector>
#include "Delegate.hpp"
#include "Base3DDef.h"

using Yx::Delegate;

class Sprite
{
	friend class SpriteMgr;
	friend class MyGfx;
public:
	enum class ShadowType 
	{
		Orth,
		Proj,
	};
	MyColor Color;
	int16_t PivotX;
	int16_t PivotY;
	bool HasShadow;
	int16_t ShadowPosX;
	int16_t ShadowPosY;
	uint16_t OverridW;
	uint16_t OverridH;
	uint16_t TexW;
	uint16_t TexH;
	inline SDL_Texture* GetTex() { return _texture; }

	Sprite() {
		PivotX = PivotY = ShadowPosX = ShadowPosY = OverridW = OverridH = 0;
		_texture = nullptr;
		_surf = nullptr;
		HasShadow = false;
		_shadow = nullptr;
		_shadowType = ShadowType::Proj;
		Color = { 255,255,255,255 };
	}
	~Sprite()
	{
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
		if (_shadow != nullptr) {
			delete _shadow;
			_shadow = nullptr;
		}
		if (_surf)
		{
			SDL_FreeSurface(_surf);
			_surf = nullptr;
		}
	}

	inline uint16_t w()
	{
		return OverridW == 0 ? TexW : OverridW;
	}
	inline uint16_t h()
	{
		return OverridH == 0 ? TexH : OverridH;
	}
	inline void ApplyColor() {
		SDL_SetTextureColorMod(_texture, Color.r, Color.g, Color.b);
		SDL_SetTextureAlphaMod(_texture, Color.a);
	}
private:
	SDL_Texture *_texture;
	SDL_Surface* _surf;
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
	bool manage;
	DrawInfo()
	{
		manage = true;
		sprite = nullptr;
	}
	~DrawInfo() {
		if (!manage) {
			delete sprite;
			sprite = nullptr;
		}
	}
	
	DrawInfo(const DrawInfo& src) = delete;
	DrawInfo& operator=(const DrawInfo&& src) = delete;

	DrawInfo(DrawInfo&& src)
	{
		sprite={ src.sprite };
		x=src.x;
		y=src.y;
		w=src.w;
		h=src.h;
		manage = src.manage;
		src.sprite = nullptr;
	}

	DrawInfo& operator=(DrawInfo&& src)
	{
		if (this != &src) {
			sprite = { src.sprite };
			x = src.x;
			y = src.y;
			w = src.w;
			h = src.h;
			manage = src.manage;
			src.sprite = nullptr;
		}
		return *this;
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
	// 设置视点，也就是屏幕中心的世界坐标
	void SetViewPoint(Vector2Float worldPos);
	void SetViewPointDelta(Vector2Float worldPos);
	const SDL_Rect *GetRenderRect();
	void SetFPS(uint16_t requireFPS);
	void Resize(uint16_t w, uint16_t h);
	void DrawWorldString(std::wstring str,int x,int y, MyColor color = { 255,255,255,255 });
	void DrawGuiString(std::wstring str, int x, int y, MyColor color = { 255,255,255,255 });
	void DrawCommand(Sprite * sprite, int x, int y, Layer layer);
	void DrawCommand(Sprite * sprite, int x, int y,int w,int h, Layer layer);
	void DrawCache();
	void RunLoop();
	void Exit();

	Sprite* CreateSpriteFromImage(Image *image);
	static Sprite* CreateSpriteFromImage(SDL_Renderer* renderer, Image * image);
	inline void SetSpriteFromSurface(Sprite* sprite,SDL_Surface *surface)
	{
		sprite->_texture = SDL_CreateTextureFromSurface(_renderer, surface);
		sprite->TexW = surface->w;
		sprite->TexH = surface->h;
		SDL_FreeSurface(surface);
	}
	// 不管理生命周期
	Sprite *CreateTextSprite(std::wstring str);
	static inline void MyGfx::GetDrawRect(DrawInfo *info,bool useOffset, __out SDL_Rect* srcRect, __out SDL_Rect* dstRect);
	static MyGfx *Instance();

	Delegate<void(uint32_t deltaMs)> onDraw;
	Delegate<void(SDL_Event*)> onEvent;

	bool mDebug;
	bool LockFrameTime;
	static TTF_Font *gFont;
private:
	SDL_Window *mWindow;

	SDL_Rect mScreenRect;
	Vector2Float _viewPoint;
	Vector2Float _worldOffset;
	std::vector<DrawInfo> mBottomCache;
	std::vector<DrawInfo> mMidCache;
	std::vector<DrawInfo> mTopCache;
	std::vector<DrawInfo> mGuiCache;
	//SDL_Surface* mScreenSurface;
	SDL_Renderer *_renderer;
	//SDL_Surface* mBgSurface;
	uint16_t mRequireFPS;
	uint16_t mFPS;

	bool mLoop;
	uint32_t mFrameTime;//ms
	uint32_t mCurrFrameTime;//ms

	inline void WorldToScreen(__in SDL_Rect &world,__out SDL_Rect &screen) {
		screen.x = world.x + _worldOffset.x;
		screen.y = world.y + _worldOffset.y;
	}
	static bool DrawInfoSort(const DrawInfo &a, const DrawInfo &b);
	static MyGfx *_inst;
};

