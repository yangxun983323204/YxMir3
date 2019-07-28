#include "MyGfx.h"
#include <algorithm>
#include <string>
#include "Utils.h"

MyGfx *MyGfx::_inst = nullptr;

MyGfx::MyGfx(std::wstring title, uint16_t w, uint16_t h)
{
	mCurrFrameTime = 0;
	SetFPS(120);
	_inst = this;
	mWindow = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	mWindow = SDL_CreateWindow(Wstr2Str(title).c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	mScreenSurface = SDL_GetWindowSurface(mWindow);
	mBgSurface = SDL_CreateRGBSurface(0, mScreenSurface->w, mScreenSurface->h, 32, 0, 0, 0, 0);
	mMidCache.reserve(w * h);
	mTopCache.reserve(w * h);
}


MyGfx::~MyGfx()
{
	auto p = mEnvSprites.begin();
	auto end = mEnvSprites.end();
	for (; p != end; p++)
	{
		delete p->second;
		p->second = nullptr;
	}
	p = mObjSprites.begin();
	end = mObjSprites.end();
	for (; p != end; p++)
	{
		delete p->second;
		p->second = nullptr;
	}
	mEnvSprites.clear();
	mObjSprites.clear();

	SDL_FreeSurface(mBgSurface);
	SDL_FreeSurface(mScreenSurface);
	if (_inst == this) {
		_inst = nullptr;
	}
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

SDL_Rect srcRect;
SDL_Rect dstRect;

void MyGfx::SetFPS(uint16_t requireFPS)
{
	mRequireFPS = requireFPS;
	mFrameTime = 1.0f / mRequireFPS;
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

void MyGfx::DrawCache()
{
	SDL_BlitSurface(mBgSurface, 0, mScreenSurface, 0);
	// draw mid
	auto p = mMidCache.begin();
	auto end = mMidCache.end();
	for (; p < end; p++)
	{
		GetDrawRect(p._Ptr, &srcRect, &dstRect);
		SDL_BlitSurface(p->sprite->Surface, &srcRect, mScreenSurface, &dstRect);
	}
	mMidCache.clear();
	// draw top
	p = mTopCache.begin();
	end = mTopCache.end();
	for (; p < end; p++)
	{
		GetDrawRect(p._Ptr, &srcRect, &dstRect);
		SDL_BlitSurface(p->sprite->Surface, &srcRect, mScreenSurface, &dstRect);
	}
	mTopCache.clear();
	//
	SDL_UpdateWindowSurface(mWindow);
}

Sprite * MyGfx::GetSprite(string wilPath, uint32_t index)
{
	auto key = wilPath + ":" + std::to_string(index);
	if (mEnvSprites.find(key)!=mEnvSprites.end())
		return mEnvSprites[key];
	else {
		ImageLib lib;
		lib.Load(wilPath);
		if (!lib.EnableAt(index))
			return nullptr;
		auto img = lib.LoadImage(index);
		auto sprite = CreateSpriteFromImage(img);
		delete img;
		mEnvSprites[key] = sprite;
		return sprite;
	}
}

void MyGfx::RunLoop()
{
	mLoop = true;
	if (onDraw)
		onDraw(mCurrFrameTime);

	bool quit = false;
	SDL_Event e;
	uint32_t preTime = SDL_GetTicks();
	uint32_t currTime = mFrameTime;
	while (mLoop)
	{
		if(SDL_PollEvent(&e)!=0)
		{
			if (onEvent)
				onEvent(&e);
		}
		else {
			currTime = SDL_GetTicks();
			mCurrFrameTime += (currTime-preTime)/1000.0f;
			preTime = currTime;
			if (mCurrFrameTime>= mFrameTime)
			{
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

	dstRect->x = info->x;
	dstRect->y = info->y;
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
