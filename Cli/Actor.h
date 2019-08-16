// 游戏对象，角色、怪物、NPC
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

struct Action
{
	bool Enable;
	ActorGender Gender;
	uint8_t Motion;
	uint32_t Current;
	uint32_t Duration;
	Direction Dir;
	union ArgUni
	{
		uint32_t ui;
		bool b;
		float f;
		int32_t si;
	};
	ArgUni Arg;
	Action() {}
	Action(uint32_t idx,ActorGender gender, Direction dir)
	{
		FrameAnim anim;
		Gender = gender;
		switch (gender)
		{
		case ActorGender::Man:
		case ActorGender::Woman:
			anim = HeroAnim[idx];
			break;
		case ActorGender::Npc:
			anim = NPCAnim[idx];
			break;
		case ActorGender::Monster:
			anim = MonsterAnim[idx];
			break;
		default:
			break;
		}
		Motion = idx;
		Current = 0;
		Duration = idx==0?0:anim.Delay * anim.Count;// 站立状态立即完成
		Dir = dir;
		Enable = true;
	}

	void Update(uint32_t ms)
	{
		Current += ms;
	}
	bool IsDone()
	{
		return Current >= Duration;
	}
};

class Actor
{
public:
	Actor();
	~Actor();

	std::function<void()> onMotionChange;
	std::function<void(Direction, uint16_t)> onMove;
	std::function<void()> onMoved;

	Feature GetFeature();
	void SetFeature(Feature f);
	uint8_t GetMotion();
	void SetMotion(uint8_t m);
	Direction GetDir();
	void SetDir(Direction dir);
	Vector2UInt GetPos();
	Action GetAction();
	void SetPos(Vector2UInt v2i);
	void Update(uint32_t delta);
	void HandleAction(Action act);
protected:
	virtual void HandleActionImpl(Action act)=0;
	bool Move(Direction dir, uint16_t speed);

	ScrollState _moveState;

	uint32_t mGUID;
	wstring mName;
	wstring mGuildName;
	Feature mFeature;
	uint8_t mMotion;
	Direction mDir;// todo 针对数种特殊生物的处理
	Vector2UInt mPos;
	uint8_t mMoveSpeed;
	uint8_t mLightRange;

	Action _action;
	Action _actionCache;
};