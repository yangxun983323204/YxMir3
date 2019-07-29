#include "SpriteMgr.h"

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
		mLibs[i].Load(WilList[i]);
	}
}

Sprite * SpriteMgr::GetSprite(uint32_t fileIdx, uint32_t imgIdx)
{
	if (!mLibs[fileIdx].EnableAt(imgIdx))
		return nullptr;

	if (mSpriteMap[fileIdx].find(imgIdx)!=mSpriteMap[fileIdx].end())
	{
		return mSpriteMap[fileIdx][imgIdx];
	}
	else {
		auto img = mLibs[fileIdx].LoadImage(imgIdx);
		Sprite *sprite = MyGfx::CreateSpriteFromImage(img);
		delete img;
		mSpriteMap[fileIdx][imgIdx] = sprite;
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
		auto p = mSpriteMap[i].begin();
		auto end = mSpriteMap[i].end();
		for (; p != end; p++)
		{
			delete p->second;
			p->second = nullptr;
		}
		mSpriteMap[i].clear();
	}
}
