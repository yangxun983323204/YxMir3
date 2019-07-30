#include "SpriteMgr.h"
#include <assert.h>

SpriteMgr *SpriteMgr::_inst = nullptr;

SpriteMgr::SpriteMgr()
{
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

SpriteMgr * SpriteMgr::Instance()
{
	if (_inst == nullptr)
	{
		_inst = new SpriteMgr();
		_inst->InitLibs();
	}
	return _inst;
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
