﻿#pragma once
#include <stdint.h>
#include "Base3DDef.h"
#include "WilIndex.h"

#define _MAX_HERO_KIND				10
#define _MAX_MON_KIND				255
#define _MAX_NPC_KIND				29

#pragma region 关于动作的定义
#define _MAX_HERO_MTN				33			// 最大动作数量				최대 동작갯수.
#define _MAX_HERO_FRAME				3000		// 转到下一个hero的最大帧数		다음 Hero로 넘어가는 최대 프레임 갯수.
#define	_MAX_HERO_REALFRAME			2640

#define _MT_STAND					0			// 闲置动作					유휴동작.
#define _MT_ARROWATTACK				1			// 弓攻击					활공격.
#define _MT_SPELL1					2			// 魔法1						마법 시전1.
#define _MT_SPELL2					3			// 魔法2						마법 공격 시전2.
#define _MT_HOLD					4			// 견디기.
#define _MT_PUSHBACK				5			// 往后推					뒤로 밀려나기.
#define _MT_PUSHBACKFLY				6			// 向后推，被挤掉				뒤로 날라서 밀려나기.
#define _MT_ATTACKMODE				7			// 战斗模式					전투모드.
#define _MT_CUT						8			// 切肉						고기 썰기.
#define _MT_ONEVSWING				9			// 单手竖斩(动作从9号到14号，根据武器的种类，决定动作。)	한손 종베기.(동작 9번부터 14번까지에서 무기의 종류에 따라 동작이 정해진다.)
#define _MT_TWOVSWING				10			// 双手竖斩					두손 종베기.
#define _MT_ONEHSWING				11			// 单手横斩					한손 횡베기.
#define _MT_TWOHSWING				12			// 双手横斩					두손 횡베기. 
#define _MT_SPEARVSWING				13			// 长枪竖斩					창 종베기.
#define _MT_SPEARHSWING				14			// 长枪横斩					창 횡베기.
#define _MT_HITTED					15			// 被击						맞기.
#define _MT_WHEELWIND				16			// 旋转着砍					돌면서 베기.
#define _MT_RANDSWING				17			// 乱砍						마구 베기.
#define _MT_BACKDROPKICK			18			// 转身踢					뒤돌아 차기.
#define _MT_DIE						19			// 死亡						죽기.
#define _MT_SPECIALDIE				20			// 特殊死亡					튀어올라 죽기.
#define _MT_WALK					21			// 走路						걷기.
#define _MT_RUN						22			// 跑						달리기.
#define _MT_MOODEPO					23			// 免助跑					무태보 뛰기.
#define _MT_ROLL					24			// 滚						구르기.
#define _MT_FISHSTAND				25			// 钓鱼模式闲置				낚시모드 유휴.
#define _MT_FISHHAND				26			// 钓鱼模式					낚시모드.
#define _MT_FISHTHROW				27			// 掷钓线					낚시줄 던지기.
#define _MT_FISHPULL				28			// 拉上钓鱼绳					낚시줄 당기기.
#define _MT_HORSESTAND				29			// 骑马模式闲置				승마모드 유휴.
#define _MT_HORSEWALK				30			// 骑马模式走					승마모드 걷기.
#define _MT_HORSERUN				31			// 骑马模式跑					승마모드 달리기.
#define _MT_HORSEHIT				32			// 骑马模式被击				승마모드 맞기.

// Monster的动作定义（定义游戏内的所有动作）										Monster의 동작 정의.(게임내의 모든 동작을 정의한다.)
#define _MAX_MON_MTN				10			// 最大动作数量				최대 동작갯수.
#define _MAX_MON_FRAME				1000		// 转到下一个Mon的最大帧数		다음 Mon로 넘어가는 최대 프레임 갯수.

#define _MT_MON_STAND				0			// 闲置动作					유휴동작.
#define _MT_MON_WALK				1			// 行走						걷기동작.
#define _MT_MON_ATTACK_A			2			// 普通攻击动作1				일반공격동작1.
#define _MT_MON_HITTED				3			// 被击动作					맞기동작.
#define _MT_MON_DIE					4			// 死亡动作					죽기동작.
#define _MT_MON_ATTACK_B			5			// 普通攻击动作2				일반공격동작2.
#define _MT_MON_SPELL_A				6			// 魔法攻击动作1				마법공격동작1.
#define _MT_MON_SPELL_B				7			// 魔法攻击动作2				마법공격동작2.
#define _MT_MON_APPEAR				8			// 显现动作					나타나기동작.
#define _MT_MON_SPECIAL_MTN			9			// 特殊动作1					특수동작1.


// NPC的操作（定义游戏内的全部动作）												NPC의 동작 정의.(게임내의 모든 동작을 정의한다.)
// NPC相关定义																NPC 관련정의.
#define _MAX_NPC_MTN				3			// 最大动作数量				최대 동작갯수.
#define _MAX_NPC_FRAME				100			// 转到下一个NPC的最大帧数		다음 NPC로 넘어가는 최대 프레임 갯수.

#define _MT_NPC_STAND				0			// 闲置动作
#define _MT_NPC_ACT01				1			// 特殊动作1
#define _MT_NPC_ACT02				2			// 特殊动作2.

// 魔法效果相关定义。
#define _MAX_EFFECT					33
#define _MAX_MAGIC					52
#define _MAX_EXPLOSION				8
#pragma endregion


#define _DEFAULT_SPELLFRAME			10
#define _DEFAULT_DELAYTIME			300

#define _HAIR_NONE					0
#define _MAX_HAIR					30

#define _WEAPON_NONE				0		
#define _MAX_WEAPON					50

#define _HORSE_NONE					0
#define _MAX_HORSE					4

#define	_MAX_WEAPON_MTN				25
#define	_MAX_WEAPON_FRAME			3000

#define	_START_HORSE_FRAME			2320
#define	_START_HORSE_MTN			29
#define	_MAX_HORSE_FRAME			400

#define _SPEED_WALK					1
#define _SPEED_RUN					2
#define _SPEED_HORSERUN				3

struct MoveState
{
	Horizontal xType;
	Vertical yType;
	int8_t xNeedScroll;
	int8_t yNeedScroll;
	float xScrolled;
	float yScrolled;
	int8_t xDir;
	int8_t yDir;
	float scrollSpeed;// 滚动cell数/每s
	uint8_t count;

	inline bool Update(uint32_t delta)
	{
		xScrolled += (xDir * CellW * scrollSpeed * delta / 1000.0f);
		yScrolled += (yDir * CellH * scrollSpeed * delta / 1000.0f);
		if ((xDir != 0 && abs(xScrolled) >= abs(xNeedScroll)) || (yDir != 0 && abs(yScrolled) >= abs(yNeedScroll))) {
			xScrolled = xNeedScroll; yScrolled = yNeedScroll;
			return false;
		}
		else
			return true;
	}
	inline void Reset()
	{
		xNeedScroll = 0; yNeedScroll = 0;
		xScrolled = 0; yScrolled = 0;
		xDir = 0; yDir = 0;
	}

	inline bool IsScrolling()
	{
		return (xNeedScroll != xScrolled) || (yNeedScroll != yScrolled);
	}

	inline void MoveState::Set(Horizontal x, Vertical y, uint8_t count = 1)
	{
		Reset();

		if (count <= 0)count = 1;
		if (count > 2)count = 2;

		this->count = count;
		if (x == Horizontal::Right) {
			xDir = -1;
			xNeedScroll = -CellW*count;
		}
		else if (x == Horizontal::Left) {
			xDir = 1;
			xNeedScroll = CellW*count;
		}

		if (y == Vertical::Down) {
			yDir = -1;
			yNeedScroll = -CellH*count;
		}
		else if (y == Vertical::Up) {
			yDir = 1;
			yNeedScroll = CellH*count;
		}
		xType = x;
		yType = y;
	}

	inline void CompleteIt()
	{
		xScrolled = xNeedScroll;
		yScrolled = yNeedScroll;
	}
};

enum class ActorGender
{
	Man = 0,
	Woman = 1,
	Monster = 3,
	Npc = 5,
};

struct Feature
{
	ActorGender Gender;
	uint8_t Dress;
	uint8_t Hair;
	uint8_t	Weapon;

	inline bool IsMan() { return Gender == ActorGender::Man; }
	inline bool IsWoman() { return Gender == ActorGender::Woman; }
	inline bool IsMonster() { return Gender == ActorGender::Monster; }
	inline bool IsNPC() { return Gender == ActorGender::Npc; }
	inline bool HasWeapon() { return  Weapon != _WEAPON_NONE; }

	inline uint16_t ImgLibIdxBase()
	{
		switch (Gender)
		{
		case ActorGender::Man:
			return _IMAGE_M_HUMAN;
		case ActorGender::Woman:
			return _IMAGE_WM_HUMAN;
		case ActorGender::Monster:
			return _IMAGE_MONSTER1;
		case ActorGender::Npc:
			return _IMAGE_NPC;
		default:
			return _IMAGE_MONSTER1;
		}
	}

	inline uint16_t HairImgLibIdx()
	{
		if (IsMan())
			return _IMAGE_M_HAIR;
		else if (IsWoman())
			return _IMAGE_WM_HAIR;
		else
			return 0;
	}

	inline uint16_t WeaponImgLibIdx()
	{
		if (HasWeapon())
		{
			if (IsMan())
				return _IMAGE_M_WEAPON1 + (Weapon - 1) / 10;
			else if (IsWoman())
				return _IMAGE_WM_WEAPON1 + (Weapon - 1) / 10;
		}
		return 0;
	}

	bool operator ==(const Feature &f)
	{
		return
			this->Gender == f.Gender &&
			this->Dress == f.Dress &&
			this->Hair == f.Hair &&
			this->Weapon == f.Weapon;
	}
};

struct FeatureEx
{
	uint8_t Horse;
	uint16_t DressColor;
	uint16_t HairColor;
};