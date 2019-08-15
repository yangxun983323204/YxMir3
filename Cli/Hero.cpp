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
	_moveState.scrollSpeed = _SPEED_WALK;
	SetMotion(_MT_WALK);
	Actor::Move(dir, _SPEED_WALK);
}

void Hero::Run(Direction dir)
{
	if (_moveState.IsScrolling())
		return;
	_moveState.scrollSpeed = _SPEED_RUN;
	SetMotion(_MT_RUN);
	Actor::Move(dir, _SPEED_RUN);
}
