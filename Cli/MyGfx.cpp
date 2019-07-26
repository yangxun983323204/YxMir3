#include "MyGfx.h"
#include <algorithm>
#include <string>

MyGfx::MyGfx(SDL_Window* window)
{
	mWindow = window;
	mScreenSurface = SDL_GetWindowSurface(window);
	mBottomCache.reserve(800 * 600);
	mMidCache.reserve(800 * 600);
	mTopCache.reserve(800 * 600);
}


MyGfx::~MyGfx()
{
	SDL_FreeSurface(mScreenSurface);
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
		mBottomCache.push_back(info);
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

SDL_Rect srcRect;
SDL_Rect dstRect;
void MyGfx::DrawCache()
{
	if (mBottomCache.size() <= 0)
		return;
	std::sort(mBottomCache.begin(), mBottomCache.end(), MyGfx::DrawInfoSort);
	// draw bottom
	auto p = mBottomCache.begin();
	auto end = mBottomCache.end();
	for (; p < end; p++)
	{
		GetDrawRect(p._Ptr,&srcRect, &dstRect);
		SDL_BlitSurface(p->sprite->Surface, &srcRect, mScreenSurface, &dstRect);
	}
	mBottomCache.clear();
	// draw mid
	p = mMidCache.begin();
	end = mMidCache.end();
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
	if (mEnvSprites.count(key))
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
	srcRect->w = info->w == 0 ? info->sprite->Surface->w : info->w;
	srcRect->h = info->h == 0 ? info->sprite->Surface->h : info->h;
	// todo 坐标计算是有问题的
	dstRect->x = info->x;
	dstRect->y = info->y;
	dstRect->w = info->w == 0 ? info->sprite->Surface->w : info->w;
	dstRect->h = info->h == 0 ? info->sprite->Surface->h : info->h;
}

bool MyGfx::DrawInfoSort(DrawInfo a, DrawInfo b)
{
	return (a.x+a.y) < (b.x+b.y);
}
