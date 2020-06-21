#include "ActorRenderer.h"
#include "SpriteMgr.h"
#include "MyGfx.h"
#include "AnimDef.h"
#include "Utils.h"

using namespace std::placeholders;


ActorRenderer::ActorRenderer()
{
	mActor = nullptr;
	Debug = false;
	_sound = new Sound3D();
}


ActorRenderer::~ActorRenderer()
{
	delete _sound;
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
	auto wpos = mActor->GetWPos();
	wpos.x -= HalfCW;
	wpos.y -= HalfCH;
	auto sprite = GetSprite(delta);
	if (sprite != nullptr)
	{
		DrawImpl(delta, wpos, sprite);
	}
	if (Debug) {
		auto gfx = MyGfx::Instance();
		// 绘制坐标信息
		gfx->DrawCommand(
			SpriteMgr::Main()->GetBuiltinSprite(SpriteMgr::IdxBuiltinCross),
			wpos.x, wpos.y, MyGfx::Layer::Top);
		char msg[256];
		auto cellPos = World2Cell(wpos);
		sprintf(msg,"(%d,%d)", cellPos.x, cellPos.y);
		gfx->DrawWorldString(YxUtils::Str2Wstr(msg), wpos.x, wpos.y + 20, {255,0,0,255});
	}
}

void ActorRenderer::DrawImpl(uint32_t delta, Vector2Float pos, Sprite *actorSprite)
{
	// 暂时保留在这，等各子类完成，这个方法清空
	//auto gfx = MyGfx::Instance();
	//// todo draw shadow
	//Sprite* shadow = nullptr;
	//auto f = mActor->GetFeature();
	//if (f.IsMan() || f.IsWoman())
	//	shadow = SpriteMgr::Main()->GetShadow(actorSprite, Sprite::ShadowType::Proj);
	//else if (f.IsMonster() && f.Dress >= 200)// 3G?
	//	shadow = SpriteMgr::Main()->GetSprite(mImgLibIdx + 1, _anim.Current);
	//else
	//	shadow = SpriteMgr::Main()->GetSprite(mImgLibIdx + _MAX_MONSTER_IMAGE, _anim.Current);
	//if (shadow)
	//	gfx->DrawCommand(shadow, pos.x + actorSprite->ShadowPosX, pos.y + actorSprite->ShadowPosY, MyGfx::Layer::Top);
	//// todo draw weapon
	//// todo draw horse
	//// draw actor
	//gfx->DrawCommand(actorSprite, pos.x, pos.y, MyGfx::Layer::Top);
	//
	//// todo draw hair
	//// todo draw effect
	//// todo draw shield
}

bool ActorRenderer::HasActor()
{
	return mActor!=nullptr;
}

Sprite * ActorRenderer::GetSprite(uint32_t delta)
{
	_anim.Update(delta);
	return SpriteMgr::Main()->GetSprite(mImgLibIdx, _anim.Current);;
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
