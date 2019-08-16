#include "Hero.h"



Hero::Hero()
{
}


Hero::~Hero()
{
}

void Hero::Walk(Direction dir)
{
	if (_moveState.IsScrolling())
		return;
	SetMotion(_MT_WALK);
	Actor::Move(dir, _SPEED_WALK);
}

void Hero::Run(Direction dir)
{
	if (_moveState.IsScrolling())
		return;
	SetMotion(_MT_RUN);
	Actor::Move(dir, _SPEED_RUN);
}

void Hero::HandleActionImpl(Action act)
{
	_action = act;
	switch (act.Motion)
	{
	case _MT_WALK:
		Walk(act.Dir);
		break;
	case _MT_RUN:
		Run(act.Dir);
		break;
	case _MT_STAND:
		SetMotion(_MT_STAND);
	default:
		break;
	}
}
