#include "ActorRenderer.h"
#include "SpriteMgr.h"
#include "MyGfx.h"
#include "AnimDef.h"

using namespace std::placeholders;


ActorRenderer::ActorRenderer()
{
	mMapRenderer = nullptr;
	mActor = nullptr;
	mCurrFrame = 0;
	mCurrDelay = 0;
	Debug = false;
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
		mActor->onMotionChange = std::bind(&ActorRenderer::OnMotionChanged, this);
		mImgLibIdx = mActor->GetFeature().ImgLibIdxBase();
		switch (actor->GetFeature().Gender)
		{
		case ActorGender::Man:
		case ActorGender::Woman:
		case ActorGender::Npc:
			break;
		case ActorGender::Monster:
			mImgLibIdx += (mActor->GetFeature().Dress / 10);
			break;
		default:
			break;
		}
	}
	OnMotionChanged();
}

void ActorRenderer::Draw(uint32_t delta)
{
	if (mActor == nullptr)
		return;
	auto gfx = MyGfx::Instance();
	auto sprite = GetSprite(delta);
	if (sprite != nullptr)
	{
		int x, y;
		CaclScreenPos(x, y);
		gfx->DrawCommand(sprite, x, y, MyGfx::Layer::Top);
		if(Debug)
			gfx->DrawGizmoCross(x, y);
	}
}

bool ActorRenderer::HasActor()
{
	return mActor!=nullptr;
}

Sprite * ActorRenderer::GetSprite(uint32_t delta)
{
	mCurrDelay += delta;
	if (mCurrDelay>=mFrameDelay)
	{
		mCurrFrame += 1;
		mCurrDelay -= mFrameDelay;
		if (mCurrFrame >= mEndFrame)
			mCurrFrame = mFstFrame;
	}
	return SpriteMgr::Instance()->GetSprite(mImgLibIdx, mCurrFrame);;
}

void ActorRenderer::CaclScreenPos(int32_t & x, int32_t & y)
{
	auto centerPos = mMapRenderer->GetPos();
	auto myPos = mActor->GetPos();
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

void ActorRenderer::OnMotionChanged()
{
	switch (mActor->GetFeature().Gender)
	{
	case ActorGender::Man:
	case ActorGender::Woman:
		mFstFrame = HeroAnim[mActor->GetMotion()].First + mActor->GetFeature().Dress*_MAX_HERO_FRAME + (uint16_t)mActor->GetDir() * 10;
		mEndFrame = mFstFrame + HeroAnim[mActor->GetMotion()].Count;
		mFrameCount = HeroAnim[mActor->GetMotion()].Count;
		mFrameDelay = HeroAnim[mActor->GetMotion()].Delay;
		break;
	case ActorGender::Npc:
		mFstFrame = NPCAnim[mActor->GetMotion()].First + mActor->GetFeature().Dress*_MAX_NPC_FRAME + (uint16_t)mActor->GetDir() * 10;
		mEndFrame = mFstFrame + NPCAnim[mActor->GetMotion()].Count;
		mFrameCount = NPCAnim[mActor->GetMotion()].Count;
		mFrameDelay = NPCAnim[mActor->GetMotion()].Delay;
		break;
	case ActorGender::Monster:
		mFstFrame = MonsterAnim[mActor->GetMotion()].First + (mActor->GetFeature().Dress % 10)*_MAX_MON_FRAME + (uint16_t)mActor->GetDir() * 10 - 1;
		mEndFrame = mFstFrame + MonsterAnim[mActor->GetMotion()].Count;
		mFrameCount = MonsterAnim[mActor->GetMotion()].Count;
		mFrameDelay = MonsterAnim[mActor->GetMotion()].Delay;
		break;
	default:
		break;
	}
	mCurrFrame = mFstFrame;
}
