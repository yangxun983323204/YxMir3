// 游戏对象，角色、怪物、NPC
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
	Vector2Float GetWPos();
	Action GetAction();
	void SetMap(Map *map) { _map = map; }
	void SetWPos(Vector2Float world);
	void Update(uint32_t delta);
	void HandleAction(Action &act);
protected:
	virtual bool HandleActionImpl(Action &act)=0;
	bool NextMoveable()
	{
		auto cPos = World2Cell(mPos);
		return _map->NextWalkable(cPos.x, cPos.y, mDir);
	}
	bool Next2Moveable()
	{
		auto cPos = World2Cell(mPos);
		return _map->Next2Walkable(cPos.x, cPos.y, mDir);
	}
	bool Move(Direction dir, float cellPerMs);

	MoveInfo _moveInfo;

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