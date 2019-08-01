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
	auto sprite = GetSprite();
	if (sprite != nullptr)
	{
		int x, y;
		CaclScreenPos(x, y);
		gfx->DrawCommand(sprite, x, y, MyGfx::Layer::Top);
	}
}

bool ActorRenderer::HasActor()
{
	return mActor!=nullptr;
}

Sprite * ActorRenderer::GetSprite()
{
	mCurrFrame = 0;
	return SpriteMgr::Instance()->GetSprite(mImgLibIdx, mCurrFrame);;
}

void ActorRenderer::CaclScreenPos(int32_t & x, int32_t & y)
{
	auto centerPos = mMapRenderer->GetPos();
	auto myPos = mActor->mPos;
	auto scroll = mMapRenderer->GetCellScrollOffset();
	x = myPos.x - centerPos.x;
	y = myPos.y - centerPos.y;
	x *= CellW;
	y *= CellH;
	x += (CellW * XCount / 2);
	y += (CellH * YCount / 2);
	x += scroll.x;
	y += scroll.y;
}
