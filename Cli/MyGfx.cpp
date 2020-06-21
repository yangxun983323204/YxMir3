#include "MyGfx.h"
#include <algorithm>
#include <string>
#include "Utils.h"

MyGfx *MyGfx::_inst = nullptr;
TTF_Font *MyGfx::gFont = nullptr;

MyGfx::MyGfx(std::wstring title, uint16_t w, uint16_t h)
{
	LockFrameTime = false;
	mCurrFrameTime = 0;
	SetFPS(60);
	_inst = this;
	mWindow = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	if (gFont == nullptr) {
		TTF_Init();
		gFont = TTF_OpenFont("./Fonts/msyh.ttf", 16);
	}
	mScreenRect.x = mScreenRect.y = 0;
	mScreenRect.w = w;
	mScreenRect.h = h;
	mWindow = SDL_CreateWindow(YxUtils::Wstr2Str(title).c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(mWindow, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED|SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0xFF);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	mBottomCache.reserve(w * h);
	mMidCache.reserve(w * h);
	mTopCache.reserve(w * h);
	mGuiCache.reserve(w * h);
}


MyGfx::~MyGfx()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(mWindow);

	if (_inst == this) {
		_inst = nullptr;
		TTF_CloseFont(gFont);
		gFont = nullptr;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
}

SDL_Rect srcRect;
SDL_Rect dstRect;

void MyGfx::SetViewPoint(Vector2Float worldPos)
{
	_viewPoint = worldPos;
	// ���Ͻ�Ϊ��Ļԭ��
	_worldOffset.x = -_viewPoint.x + mScreenRect.w / 2.0;
	_worldOffset.y = -_viewPoint.y + mScreenRect.h / 2.0;
}

void MyGfx::SetViewPointDelta(Vector2Float pos)
{
	_viewPoint.x += pos.x;
	_viewPoint.y += pos.y;
	SetViewPoint(_viewPoint);
}

const SDL_Rect * MyGfx::GetRenderRect()
{
	return &mScreenRect;
}

void MyGfx::SetFPS(uint16_t requireFPS)
{
	mRequireFPS = requireFPS;
	mFrameTime = 1000 / mRequireFPS;
}

void MyGfx::Resize(uint16_t w, uint16_t h)
{
	if (mScreenRect.w == w && mScreenRect.h == h)
	{
		return;
	}
	SDL_SetWindowSize(mWindow, w, h);
	mScreenRect.w = w;
	mScreenRect.h = h;
	if (_renderer)
	{
		_renderer = SDL_CreateRenderer(mWindow, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED | SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0xFF);
	}
}

void MyGfx::DrawWorldString(std::wstring str, int x, int y, MyColor color)
{
	auto sp = CreateTextSprite(str);
	sp->Color = color;
	DrawInfo info;
	info.x = x;
	info.y = y;
	info.w = sp->TexW;
	info.h = sp->TexH;
	info.sprite = sp;
	mTopCache.push_back(std::move(info));
	mTopCache[mTopCache.size()-1].manage = false;
}

void MyGfx::DrawGuiString(std::wstring str, int x, int y, MyColor color)
{
	auto sp = CreateTextSprite(str);
	sp->Color = color;
	DrawInfo info;
	info.x = x;
	info.y = y;
	info.w = sp->TexW;
	info.h = sp->TexH;
	info.sprite = sp;
	mGuiCache.push_back(std::move(info));
	mGuiCache[mGuiCache.size() - 1].manage = false;
}

void MyGfx::DrawCommand(Sprite * sprite, int x, int y, Layer layer)
{
	DrawCommand(sprite,x,y,sprite->w(),sprite->h(),layer);
}

void MyGfx::DrawCommand(Sprite * sprite, int x, int y, int w, int h, Layer layer)
{
	DrawInfo info;
	info.sprite = sprite;
	info.x = x;
	info.y = y;
	info.w = w;
	info.h = h;
	switch (layer)
	{
	case MyGfx::Bottom:
		mBottomCache.push_back(std::move(info));
		break;
	case MyGfx::Mid:
		mMidCache.push_back(std::move(info));
		break;
	case MyGfx::Top:
		mTopCache.push_back(std::move(info));
		break;
	case MyGfx::GUI:
		mGuiCache.push_back(std::move(info));
		break;
	default:
		break;
	}
}

void MyGfx::DrawCache()
{
	SDL_RenderClear(_renderer);
	if (mDebug) DrawGuiString(L"fps:" + std::to_wstring(mFPS), 0, 0, {255,0,0,255});
	// bottom
	auto p = mBottomCache.begin();
	auto end = mBottomCache.end();
	for (; p != end; p++)
	{
		GetDrawRect(p._Ptr, true, &srcRect, &dstRect);
		WorldToScreen(dstRect, dstRect);
		if (SDL_HasIntersection(&dstRect, &mScreenRect))
			SDL_RenderCopy(_renderer, p->sprite->_texture, &srcRect, &dstRect);
	}
	mBottomCache.clear();
	// draw mid
	p = mMidCache.begin();
	end = mMidCache.end();
	for (; p != end; p++)
	{
		GetDrawRect(p._Ptr,true, &srcRect, &dstRect);
		WorldToScreen(dstRect, dstRect);
		if(SDL_HasIntersection(&dstRect, &mScreenRect))
			SDL_RenderCopy(_renderer, p->sprite->_texture, &srcRect, &dstRect);
	}
	mMidCache.clear();
	// draw top
	p = mTopCache.begin();
	end = mTopCache.end();
	for (; p != end; p++)
	{
		GetDrawRect(p._Ptr,true, &srcRect, &dstRect);
		WorldToScreen(dstRect, dstRect);
		if (SDL_HasIntersection(&dstRect, &mScreenRect)) {
			p->sprite->ApplyColor();
			SDL_RenderCopy(_renderer, p->sprite->_texture, &srcRect, &dstRect);
		}
	}
	mTopCache.clear();
	// draw gui
	p = mGuiCache.begin();
	end = mGuiCache.end();
	for (; p != end; p++)
	{
		GetDrawRect(p._Ptr,false, &srcRect, &dstRect);
		if (SDL_HasIntersection(&dstRect, &mScreenRect)) {
			p->sprite->ApplyColor();
			SDL_RenderCopy(_renderer, p->sprite->_texture, &srcRect, &dstRect);
		}
	}
	mGuiCache.clear();
	//
	SDL_RenderPresent(_renderer);
}

void MyGfx::RunLoop()
{
	mLoop = true;
	if (onDraw)
		onDraw(mCurrFrameTime);

	bool quit = false;
	SDL_Event e;
	auto preTime = SDL_GetTicks();
	auto currTime = mFrameTime;
	while (mLoop)
	{
		if(SDL_PollEvent(&e)!=0)
		{
			if (onEvent)
				onEvent(&e);
		}
		else {
			currTime = SDL_GetTicks();
			auto delta = currTime - preTime;
			mCurrFrameTime += delta;
			preTime = currTime;
			if (mCurrFrameTime > mFrameTime)
			{
				if (LockFrameTime) mCurrFrameTime = mFrameTime;
				mFPS = ceil(1 / (mCurrFrameTime/1000.0f));
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

	auto surface = SDL_CreateRGBSurfaceFrom(
		(void*)(image->Pixels), 
		image->Width, image->Height,
		32, 4 * image->Width,
		ImageLib::MaskR, ImageLib::MaskG, ImageLib::MaskB, ImageLib::MaskA);

	sprite->_texture = SDL_CreateTextureFromSurface(_renderer, surface);
	sprite->TexW = surface->w;
	sprite->TexH = surface->h;
	if(sprite->HasShadow)
		sprite->_surf = surface;
	else {
		sprite->_surf = nullptr;
		SDL_FreeSurface(surface);
	}

	return sprite;
}

Sprite* MyGfx::CreateSpriteFromImage(SDL_Renderer* renderer,Image * image)
{
	auto sprite = new Sprite();
	sprite->PivotX = image->PivotX;
	sprite->PivotY = image->PivotY;
	sprite->HasShadow = image->HasShadow != 0;
	sprite->ShadowPosX = image->ShadowPosX;
	sprite->ShadowPosY = image->ShadowPosY;

	auto surface = SDL_CreateRGBSurfaceFrom(
		(void*)(image->Pixels),
		image->Width, image->Height,
		32, 4 * image->Width,
		ImageLib::MaskR, ImageLib::MaskG, ImageLib::MaskB, ImageLib::MaskA);

	sprite->_texture = SDL_CreateTextureFromSurface(renderer, surface);
	sprite->TexW = surface->w;
	sprite->TexH = surface->h;
	if (sprite->HasShadow)
		sprite->_surf = surface;
	else {
		sprite->_surf = nullptr;
		SDL_FreeSurface(surface);
	}

	return sprite;
}

inline void MyGfx::GetDrawRect(DrawInfo *info,bool useOffset,__out SDL_Rect* srcRect, __out SDL_Rect* dstRect)
{
	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->w = info->w;
	srcRect->h = info->h;
	if (useOffset) {
		dstRect->x = info->x + info->sprite->PivotX;
		dstRect->y = info->y + info->sprite->PivotY;
	}
	else {
		dstRect->x = info->x;
		dstRect->y = info->y;
	}
	dstRect->w = info->w;
	dstRect->h = info->h;
}

MyGfx * MyGfx::Instance()
{
	return _inst;
}

Sprite * MyGfx::CreateTextSprite(std::wstring str)
{
	SDL_Surface* textSurface = TTF_RenderUTF8_Solid(gFont, YxUtils::Wstr2Str(str).c_str(), SDL_Color{ 255,255,255,255 });
	Sprite *sp = new Sprite();
	SetSpriteFromSurface(sp, textSurface);
	return sp;
}

bool MyGfx::DrawInfoSort(const DrawInfo &a, const DrawInfo &b)
{
	if (a.x != b.x)
		return a.y <= b.y;
	else
		return a.x <= b.x;
}
