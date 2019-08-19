#include "Hero.h"



Hero::Hero()
{
}


Hero::~Hero()
{
}

bool Hero::Walk(Action &act)
{
	if (_moveState.IsScrolling())
		return false;
	SetDir(act.Dir);
	if (!NextMoveable())
		return false;
	SetMotion(_MT_WALK);
	Actor::Move(act.Dir, _SPEED_WALK);
	act.MarkMove(true, _SPEED_WALK);
	return true;
}

bool Hero::Run(Action &act)
{
	if (_moveState.IsScrolling())
		return false;
	SetDir(act.Dir);
	if (!Next2Moveable())// 第二格不能走，变为移动
	{
		act = Action(_MT_WALK, act.Gender, act.Dir);
		return Walk(act);
	}
	if (!NextMoveable())
		return false;
	SetMotion(_MT_RUN);
	Actor::Move(act.Dir, _SPEED_RUN);
	act.MarkMove(true, _SPEED_RUN);
	return true;
}

bool Hero::HandleActionImpl(Action &act)
{
	switch (act.Motion)
	{
	case _MT_WALK:
		return Walk(act);
	case _MT_RUN:
		return Run(act);
	case _MT_STAND:
		SetMotion(_MT_STAND);
		return true;
	default:
		return false;
	}
}
