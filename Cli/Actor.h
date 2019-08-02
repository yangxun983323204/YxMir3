﻿// 游戏对象，角色、怪物、NPC
#pragma once
#include "WILIndex.h"
#include <stdint.h>
#include "Common.h"
#include "AnimDef.h"
#include <functional>

using std::wstring;

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

	inline bool IsMan(){ return Gender == ActorGender::Man; }
	inline bool IsWoman() { return Gender == ActorGender::Woman; }
	inline bool IsMonster() { return Gender == ActorGender::Monster; }
	inline bool IsNPC() { return Gender == ActorGender::Npc; }
	inline bool HasWeapon() { return  Weapon != 0; }

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
			break;
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
			if(IsMan())
				return _IMAGE_M_WEAPON1 + (Weapon - 1) / 10;
			else if(IsWoman())
				return _IMAGE_WM_WEAPON1 + (Weapon - 1) / 10;
		}
		return 0;
	}
};

struct FeatureEx
{
	uint8_t Horse;
	uint16_t DressColor;
	uint16_t HairColor;
};

class Actor
{
public:
	Actor();
	~Actor();

	std::function<void()> onMotionChange;

	uint32_t mGUID;
	wstring mName;
	wstring mGuildName;
	Feature mFeature;
	uint8_t mMotion;
	Direction mDir;// todo 针对数种特殊生物的处理
	Vector2UInt mPos;
	uint8_t mMoveSpeed;
	uint8_t mLightRange;
};