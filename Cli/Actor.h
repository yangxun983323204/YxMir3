﻿// 游戏对象，角色、怪物、NPC
#pragma once
#include "WILIndex.h"
#include <stdint.h>
#include "Common.h"
#include "AnimDef.h"
#include <functional>
#include "Delegate.hpp"
#include "Map.h"

using std::wstring;

class Actor
{
public:
	Actor();
	~Actor();

	std::function<void()> onMotionChange;
	Yx::Delegate<void(Action*)> onActionStart;
	Yx::Delegate<void(Action*)> onActionCompleted;

	Feature GetFeature();
	void SetFeature(Feature f);
	uint8_t GetMotion();
	void SetMotion(uint8_t m);
	Direction GetDir();
	void SetDir(Direction dir);
	Vector2Float GetPos();
	Action GetAction();
	void SetMap(Map *map) { _map = map; }
	void SetPos(Vector2Float v2i);
	void Update(uint32_t delta);
	void HandleAction(Action &act);
	void CompleteMove() {
		_moveState.CompleteIt();
		//SetPos(Vector2Float{ mPos.x - _moveState.xDir*_moveState.count, mPos.y - _moveState.yDir*_moveState.count });
		SetPos(Vector2Float{ mPos.x - _moveState.xScrolled, mPos.y - _moveState.yScrolled });
	}
protected:
	virtual bool HandleActionImpl(Action &act)=0;
	bool NextMoveable()
	{
		return _map->NextWalkable(mPos.x, mPos.y, mDir);
	}
	bool Next2Moveable()
	{
		return _map->Next2Walkable(mPos.x, mPos.y, mDir);
	}
	bool Move(Direction dir, uint16_t speed);

	MoveState _moveState;

	uint32_t mGUID;
	wstring mName;
	wstring mGuildName;
	Feature mFeature;
	uint8_t mMotion;
	Direction mDir;// todo 针对数种特殊生物的处理
	Vector2Float mPos;
	uint8_t mMoveSpeed;
	uint8_t mLightRange;

	Action _action;
	Action _actionCache;

	Map *_map;
};