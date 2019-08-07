#include "MyGfx.h"
#include <algorithm>
#include <string>
#include "Utils.h"

MyGfx *MyGfx::_inst = nullptr;
TTF_Font *MyGfx::gFont = TTF_OpenFont("./Fonts/STSONG.TTF", 16);
//
bool MyGfx::Inited = false;
uint16_t MyGfx::BuiltinSpriteCount = 0;
Sprite** MyGfx::BuiltinSprite = nullptr;

void MyGfx::Init()
{
	if (MyGfx::Inited)
		return;
	Inited = true;
	BuiltinSpriteCount = 1;
	BuiltinSprite = new Sprite*[BuiltinSpriteCount];
	uint8_t size = 15;
	uint8_t half_up = ceil(size / 2.0f);
	uint8_t half_down = floor(size / 2.0f);
	// ¡°+¡±·ûºÅ¾«Áé
	auto cross = new Sprite();
	cross->PivotX = half_up;
	cross->PivotY = -half_up;
	cross->Surface = SDL_CreateRGBSurface(0, size, size, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0xff);
	SDL_FillRect(cross->Surface, 0, 0x000000);
	SDL_LockSurface(cross->Surface);
	auto p = (uint32_t*)(cross->Surface->pixels);
	for (uint8_t i = 0; i < size; i++)
	{
		p[half_down * size + i] = 0xff0000ff;
		p[i * size + half_down] = 0xff0000ff;
	}
	SDL_UnlockSurface(cross->Surface);
	BuiltinSprite[0] = cross;
}
//

MyGfx::MyGfx(std::wstring title, uint16_t w, uint16_t h)
{
	Init();
	mCurrFrameTime = 0;
	SetFPS(120);
	_inst = this;
	mWindow = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	if (gFont == nullptr) {
		TTF_Init();
		gFont = TTF_OpenFont("./Fonts/STSONG.TTF", 28);
	}
	mScreenRect.x = mScreenRect.y = 0;
	mScreenRect.w = w;
	mScreenRect.h = h;
	mWindow = SDL_CreateWindow(Wstr2Str(title).c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	mScreenSurface = SDL_GetWindowSurface(mWindow);
	mBgSurface = SDL_CreateRGBSurface(0, mScreenSurface->w, mScreenSurface->h, 32, 0, 0, 0, 0);
	mMidCache.reserve(w * h);
	mTopCache.reserve(w * h);
}


MyGfx::~MyGfx()
{
	SDL_FreeSurface(mBgSurface);
	SDL_FreeSurface(mScreenSurface);
	SDL_DestroyWindow(mWindow);

	if (_inst == this) {
		_inst = nullptr;
		TTF_CloseFont(gFont);
		gFont = nullptr;
		TTF_Quit();
		SDL_Quit();
	}
}

SDL_Rect srcRect;
SDL_Rect dstRect;

const SDL_Rect * MyGfx::GetRenderRect()
{
	return &mScreenRect;
}

void MyGfx::SetFPS(uint16_t requireFPS)
{
	mRequireFPS = requireFPS;
	mFrameTime = 1.0f / mRequireFPS;
}

void MyGfx::DrawString(std::wstring str, int x, int y)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, Wstr2Str(str).c_str(), SDL_Color{0,255,0,255});
	TempDrawInfo info;
	info.x = x;
	info.y = y;
	info.w = textSurface->w;
	info.h = textSurface->h;
	mTopCache.push_back(info);
	mTopCache[mTopCache.size()-1].sprite = new Sprite();
	mTopCache[mTopCache.size() - 1].sprite->Surface = textSurface;
}

void MyGfx::DrawCommand(Sprite * sprite, int x, int y, Layer layer)
{
	DrawInfo info;
	info.sprite = sprite;
	info.x = x;
	info.y = y;
	info.w = sprite->w();
	info.h = sprite->h();
	switch (layer)
	{
	case MyGfx::Bottom:
		GetDrawRect(&info, &srcRect, &dstRect);
		SDL_BlitSurface(sprite->Surface, &srcRect, mBgSurface, &dstRect);
		break;
	case MyGfx::Mid:
		mMidCache.push_back(info);
		break;
	case MyGfx::Top:
		mTopCache.push_back(info);
		break;
	default:
		break;
	}
}

void MyGfx::DrawGizmoCross(int x, int y)
{
	DrawInfo info;
	info.sprite = BuiltinSprite[0];
	info.x = x;
	info.y = y;
	info.w = info.sprite->w();
	info.h = info.sprite->h();
	mTopCache.push_back(info);
}

void MyGfx::DrawCache()
{
	if (mDebug)
		DrawString(L"fps:" + std::to_wstring(mFPS), 0, 0);

	SDL_FillRect(mScreenSurface, 0, 0);
	SDL_BlitSurface(mBgSurface, 0, mScreenSurface, 0);
	// draw mid
	auto p = mMidCache.begin();
	auto end = mMidCache.end();
	for (; p < end; p++)
	{
		GetDrawRect(p._Ptr, &srcRect, &dstRect);
		if(SDL_HasIntersection(&dstRect, &mScreenRect))
			SDL_BlitSurface(p->sprite->Surface, &srcRect, mScreenSurface, &dstRect);
	}
	mMidCache.clear();
	// draw top
	p = mTopCache.begin();
	end = mTopCache.end();
	for (; p < end; p++)
	{
		GetDrawRect(p._Ptr, &srcRect, &dstRect);
		if (SDL_HasIntersection(&dstRect, &mScreenRect))
			SDL_BlitSurface(p->sprite->Surface, &srcRect, mScreenSurface, &dstRect);
	}
	mTopCache.clear();
	//
	SDL_UpdateWindowSurface(mWindow);
}

void MyGfx::RunLoop()
{
	mLoop = true;
	if (onDraw)
		onDraw(mCurrFrameTime);

	bool quit = false;
	SDL_Event e;
	float preTime = SDL_GetTicks()/1000.0f;
	float currTime = mFrameTime;
	while (mLoop)
	{
		if(SDL_PollEvent(&e)!=0)
		{
			if (onEvent)
				onEvent(&e);
		}
		else {
			currTime = SDL_GetTicks()/1000.0f;
			float delta = currTime - preTime;
			mCurrFrameTime += delta;
			preTime = currTime;
			if (mCurrFrameTime > mFrameTime)
			{
				mFPS = ceil(1 / mCurrFrameTime);
				if (onDraw)
					onDraw(mCurrFrameTime);
				mCurrFrameTime = 0;
			}
		}
	}
}

void MyGfx::Exit()
{
	mLoop = false;
}

Sprite* MyGfx::CreateSpriteFromImage(Image * image)
{
	auto sprite = new Sprite();
	sprite->PivotX = image->PivotX;
	sprite->PivotY = image->PivotY;
	sprite->HasShadow = image->HasShadow != 0;
	sprite->ShadowPosX = image->ShadowPosX;
	sprite->ShadowPosY = image->ShadowPosY;

	sprite->Surface = SDL_CreateRGBSurfaceFrom(
		(void*)(image->Pixels), 
		image->Width, image->Height,
		32, 4 * image->Width,
		MyColor::MaskR, MyColor::MaskG, MyColor::MaskB, MyColor::MaskA);

	return sprite;
}

inline void MyGfx::GetDrawRect(DrawInfo *info,__out SDL_Rect* srcRect, __out SDL_Rect* dstRect)
{
	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->w = info->w;
	srcRect->h = info->h;

	dstRect->x = info->x - info->sprite->PivotX;
	dstRect->y = info->y + info->sprite->PivotY;
	dstRect->w = info->w;
	dstRect->h = info->h;
}

MyGfx * MyGfx::Instance()
{
	return _inst;
}

bool MyGfx::DrawInfoSort(DrawInfo a, DrawInfo b)
{
	return (a.x+a.y) < (b.x+b.y);
}
