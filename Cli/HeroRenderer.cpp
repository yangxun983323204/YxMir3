#include "HeroRenderer.h"
#include "SpriteMgr.h"
#include <assert.h>

HeroRenderer::HeroRenderer()
{
}


HeroRenderer::~HeroRenderer()
{
}

void HeroRenderer::DrawImpl(uint32_t delta, Vector2Int pos, Sprite * actorSprite)
{
	Sprite* shadow = nullptr;
	Sprite* weapon = nullptr;
	Sprite* horse = nullptr;
	Sprite* hair = nullptr;
	Sprite* effect = nullptr;
	Sprite* shield = nullptr;

	auto gfx = MyGfx::Instance();
	// get shadow
	auto f = mActor->GetFeature();
	assert(f.IsMan() || f.IsWoman());
	shadow = SpriteMgr::Instance()->GetShadow(actorSprite, Sprite::ShadowType::Proj);
	// get weapon
	uint32_t fWeapon;
	if (f.Weapon == 254)// 3g?
		fWeapon = ((f.Weapon - 2) % 10)*_MAX_WEAPON_FRAME + _anim.Current - _MAX_HERO_FRAME*f.Dress;
	else
		fWeapon = ((f.Weapon - 1) % 10)*_MAX_WEAPON_FRAME + _anim.Current - _MAX_HERO_FRAME*f.Dress;
	weapon = SpriteMgr::Instance()->GetSprite(f.WeaponImgLibIdx(), fWeapon);
	// todo get horse
	// get hair
	uint32_t fHair = f.Hair*_MAX_HERO_FRAME - _MAX_HERO_FRAME + _anim.Current - _MAX_HERO_FRAME*f.Dress;
	hair = SpriteMgr::Instance()->GetSprite(f.HairImgLibIdx(), fHair);
	// todo get effect
	// todo get shield

	// ���ӵ�������˳�����һϵ��Ԫ��
	if (shadow)
		gfx->DrawCommand(shadow, pos.x + actorSprite->ShadowPosX, pos.y + actorSprite->ShadowPosY, MyGfx::Layer::Mid);
	auto dir = mActor->GetDir();
	// ��ĳЩ�����Ȼ����ٻ�����������һЩ�������෴
	if (dir > Direction::Up && dir <= Direction::Down)
	{
		gfx->DrawCommand(actorSprite, pos.x, pos.y, MyGfx::Layer::Mid);
		if (weapon)
			gfx->DrawCommand(weapon, pos.x, pos.y, MyGfx::Layer::Mid);
	}
	else {
		if (weapon)
			gfx->DrawCommand(weapon, pos.x, pos.y, MyGfx::Layer::Mid);
		gfx->DrawCommand(actorSprite, pos.x, pos.y, MyGfx::Layer::Mid);
	}
	if(hair)
		gfx->DrawCommand(hair, pos.x, pos.y, MyGfx::Layer::Mid);

	PlayActionSound();
}
// todo
void HeroRenderer::PlayActionSound()
{
	int waveNum = -1;
	auto motion = mActor->GetMotion();
	if (motion == _MT_WALK || motion == _MT_RUN || 
		motion == _MT_HORSEWALK || motion == _MT_HORSERUN || 
		motion == _MT_MOODEPO || motion == _MT_PUSHBACK)
	{
		if (_anim.Current == _anim.End - 5 || false/*�ж�Ԥ��ʧ�ܣ�*/) // ���
			waveNum = 1;
		if (_anim.Current == _anim.End - 2 || false/*�ж�Ԥ��ʧ�ܣ�*/) // �ҽ�
			waveNum = 1;
	}
	else if (_anim.Current == _anim.First+1 && motion == _MT_HITTED)
	{
		// �ܻ���Ч
	}
	else if (_anim.Current == _anim.First + 2 && motion == _MT_HITTED)
	{
		// �ܻ���Ч2
	}
	else if (_anim.Current == _anim.First + 1 && motion == _MT_DIE)
	{
		// ������Ч
	}
	else if (_anim.Current == _anim.First + 1 && motion >= _MT_ONEVSWING && motion <= _MT_SPEARHSWING)
	{
		// ������Ч
	}
	else if (_anim.Current == _anim.First + 2 && motion >= _MT_ONEVSWING && motion <= _MT_SPEARHSWING)
	{
		// ������Ч2
	}
	else if (_anim.Current == _anim.First + 1 && (motion == _MT_SPELL1|| motion == _MT_SPELL2))
	{
		// ʩ����Ч
	}
	if (waveNum!=-1)
	{
		_sound->LoadWave(waveNum);
		_sound->Play(false);
	}
	_sound->UpdatePos(mActor->GetPos());
}
