#include "ActorRenderer.h"
#include "SpriteMgr.h"
#include "MyGfx.h"


ActorRenderer::ActorRenderer()
{
}


ActorRenderer::~ActorRenderer()
{
}

void ActorRenderer::SetMapRenderer(MapRenderer *mapRenderer)
{
	mMapRenderer = mapRenderer;
}

void ActorRenderer::SetActor(Actor * actor)
{
	mActor = actor;
	if (mActor!=nullptr)
	{
		mImgLibIdx = mActor->mFeature.ImgLibIdx();
	}
}

void ActorRenderer::Draw(uint32_t delta)
{
	if (mActor == nullptr)
		return;
	auto gfx = MyGfx::Instance();
	if (!IsFarLeftScreen())
	{
		auto sprite = SpriteMgr::Instance()->GetSprite(mImgLibIdx, mCurrFrame);
		if (sprite != nullptr)
		{
			// todo 坐标要用世界转屏幕
			gfx->DrawCommand(sprite, mActor->PosX, mActor->PosY, MyGfx::Layer::Top);
		}
	}
}

bool ActorRenderer::HasActor()
{
	return mActor!=nullptr;
}

bool ActorRenderer::IsFarLeftScreen()
{
	// todo
	return true;
}
