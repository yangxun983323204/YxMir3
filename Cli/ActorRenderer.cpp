#include "ActorRenderer.h"
#include "SpriteMgr.h"
#include "MyGfx.h"
#include "AnimDef.h"

using namespace std::placeholders;


ActorRenderer::ActorRenderer()
{
	mMapRenderer = nullptr;
	mActor = nullptr;
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
	auto sprite = GetSprite(delta);
	if (sprite != nullptr)
	{
		Vector2Int pos;
		CaclScreenPos(pos.x, pos.y);
		DrawImpl(delta, pos, sprite);
	}
}

void ActorRenderer::DrawImpl(uint32_t delta, Vector2Int pos, Sprite *actorSprite)
{
	// 暂时保留在这，等各子类完成，这个方法清空
	auto gfx = MyGfx::Instance();
	// todo draw shadow
	Sprite* shadow = nullptr;
	auto f = mActor->GetFeature();
	if (f.IsMan() || f.IsWoman())
		shadow = SpriteMgr::Instance()->GetShadow(actorSprite, Sprite::ShadowType::Proj);
	else if (f.IsMonster() && f.Dress >= 200)// 3G?
		shadow = SpriteMgr::Instance()->GetSprite(mImgLibIdx + 1, _anim.Current);
	else
		shadow = SpriteMgr::Instance()->GetSprite(mImgLibIdx + _MAX_MONSTER_IMAGE, _anim.Current);
	if (shadow)
		gfx->DrawCommand(shadow, pos.x + actorSprite->ShadowPosX, pos.y + actorSprite->ShadowPosY, MyGfx::Layer::Top);
	// todo draw weapon
	// todo draw horse
	// draw actor
	gfx->DrawCommand(actorSprite, pos.x, pos.y, MyGfx::Layer::Top);
	if (Debug) {
		gfx->DrawCommand(
			SpriteMgr::Instance()->GetBuiltinSprite(SpriteMgr::IdxBuiltinCross),
			pos.x, pos.y, MyGfx::Layer::Top);
	}
	// todo draw hair
	// todo draw effect
	// todo draw shield
}

bool ActorRenderer::HasActor()
{
	return mActor!=nullptr;
}

Sprite * ActorRenderer::GetSprite(uint32_t delta)
{
	_anim.Update(delta);
	return SpriteMgr::Instance()->GetSprite(mImgLibIdx, _anim.Current);;
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
		_anim.Reset(HeroAnim[mActor->GetMotion()], mActor->GetFeature().Dress*_MAX_HERO_FRAME + (uint16_t)mActor->GetDir() * 10);
		break;
	case ActorGender::Npc:
		_anim.Reset(NPCAnim[mActor->GetMotion()], mActor->GetFeature().Dress*_MAX_NPC_FRAME + (uint16_t)mActor->GetDir() * 10);
		break;
	case ActorGender::Monster:
		_anim.Reset(MonsterAnim[mActor->GetMotion()], (mActor->GetFeature().Dress % 10)*_MAX_MON_FRAME + (uint16_t)mActor->GetDir() * 10 - 1);
		break;
	default:
		break;
	}
}
