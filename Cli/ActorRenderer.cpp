#include "ActorRenderer.h"
#include "SpriteMgr.h"
#include "MyGfx.h"
#include "AnimDef.h"

using namespace std::placeholders;


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
		mActor->onMotionChange = std::bind(&ActorRenderer::OnMotionChanged, this);
		mImgLibIdx = mActor->mFeature.ImgLibIdxBase();
		switch (actor->mFeature.Gender)
		{
		case ActorGender::Man:
		case ActorGender::Woman:
		case ActorGender::Npc:
			break;
		case ActorGender::Monster:
			mImgLibIdx += (mActor->mFeature.Dress / 10);
			break;
		default:
			break;
		}
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
		gfx->DrawGizmoCross(x, y);
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

void ActorRenderer::OnMotionChanged()
{
	switch (mActor->mFeature.Gender)
	{
	case ActorGender::Man:
	case ActorGender::Woman:
		mFstFrame = HeroAnim[mActor->mMotion].First + mActor->mFeature.Dress*_MAX_HERO_FRAME + (uint16_t)mActor->mDir * 10;
		mEndFrame = mFstFrame + HeroAnim[mActor->mMotion].Count;
		mFrameDelay = HeroAnim[mActor->mMotion].Delay;
		break;
	case ActorGender::Npc:
		mFstFrame = NPCAnim[mActor->mMotion].First + mActor->mFeature.Dress*_MAX_NPC_FRAME + (uint16_t)mActor->mDir * 10;
		mEndFrame = mFstFrame + NPCAnim[mActor->mMotion].Count;
		mFrameDelay = NPCAnim[mActor->mMotion].Delay;
		break;
	case ActorGender::Monster:
		mFstFrame = MonsterAnim[mActor->mMotion].First + (mActor->mFeature.Dress % 10)*_MAX_MON_FRAME + (uint16_t)mActor->mDir * 10 - 1;
		mEndFrame = mFstFrame + MonsterAnim[mActor->mMotion].Count;
		mFrameDelay = MonsterAnim[mActor->mMotion].Delay;
		break;
	default:
		break;
	}
}
