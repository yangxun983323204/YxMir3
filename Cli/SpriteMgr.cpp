#include "SpriteMgr.h"
#include <assert.h>

SpriteMgr *SpriteMgr::_inst = nullptr;
//
bool SpriteMgr::Inited = false;
uint16_t SpriteMgr::BuiltinSpriteCount = 0;
Sprite** SpriteMgr::BuiltinSprite = nullptr;

const uint8_t SpriteMgr::IdxBuiltinCross = 0;

void SpriteMgr::Init()
{
	if (SpriteMgr::Inited)
		return;
	Inited = true;
	BuiltinSpriteCount = 1;
	BuiltinSprite = new Sprite*[BuiltinSpriteCount];
	uint8_t size = 15;
	uint8_t half_up = ceil(size / 2.0f);
	uint8_t half_down = floor(size / 2.0f);
	// “+”符号精灵
	auto cross = new Sprite();
	cross->PivotX = -half_down + CellW / 2;// 坐标在左上角，因此要绘制在格子中心，需要向右下移半格
	cross->PivotY = -half_down + CellH / 2;
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
	BuiltinSprite[IdxBuiltinCross] = cross;
}
//

SpriteMgr::SpriteMgr()
{
	Init();
}


SpriteMgr::~SpriteMgr()
{
	ClearCache();
	if (_inst == this)
	{
		_inst = nullptr;
	}
}

void SpriteMgr::InitLibs()
{
	for (size_t i = 0; i < _MAX_IMAGE; i++)
	{
		if (mLibs[i].Load(WilList[i])) {
			auto record = &mSpriteMap[i];
			record->size = mLibs[i].ImgCount();
			record->sprites = new Sprite*[record->size]{nullptr};
		}
		else {
			mSpriteMap[i].size = 0;
			mSpriteMap[i].sprites = nullptr;
		}
	}
}

Sprite * SpriteMgr::GetSprite(uint32_t fileIdx, uint32_t imgIdx)
{
	if (!mLibs[fileIdx].IsLoaded())
		return nullptr;
	if (!mLibs[fileIdx].EnableAt(imgIdx))
		return nullptr;
	auto sp = mSpriteMap[fileIdx].sprites[imgIdx];
	if (sp!=nullptr)
	{
		return sp;
	}
	else {
		auto img = mLibs[fileIdx].LoadImage(imgIdx);
		Sprite *sprite = MyGfx::CreateSpriteFromImage(img);
		delete img;
		assert(sprite != nullptr);
		mSpriteMap[fileIdx].sprites[imgIdx] = sprite;
		return sprite;
	}
}

Sprite * SpriteMgr::GetProjShadow(Sprite * base, Sprite::ShadowType type)
{
	if (base->_shadow == nullptr || base->_shadowType != type) {
		if (base->_shadow) {
			delete base->_shadow;
			base->_shadow = nullptr;
		}
		if (type == Sprite::ShadowType::Orth)
			base->_shadow = CreateOrthShadow(base);
		else if (type == Sprite::ShadowType::Proj)
			base->_shadow = CreateProjShadow(base);
	}
	return base->_shadow;
}

Sprite * SpriteMgr::GetBuiltinSprite(uint8_t idx)
{
	return BuiltinSprite[idx];
}

SpriteMgr * SpriteMgr::Instance()
{
	if (_inst == nullptr)
	{
		_inst = new SpriteMgr();
		_inst->InitLibs();
	}
	return _inst;
}

Sprite * SpriteMgr::CreateOrthShadow(Sprite * base)
{
	return nullptr;// TODO
}

Sprite * SpriteMgr::CreateProjShadow(Sprite * base)
{
	return nullptr;// TODO
}

void SpriteMgr::ClearCache()
{
	for (size_t i = 0; i < _MAX_IMAGE; i++)
	{
		auto size = mSpriteMap[i].size;
		for (size_t j = 0; j < size; j++)
		{
			auto p = mSpriteMap[i].sprites[j];
			delete p;
		}
		delete mSpriteMap[i].sprites;
		mSpriteMap[i].sprites = nullptr;
	}
}
