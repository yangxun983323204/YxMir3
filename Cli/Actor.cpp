#include "Actor.h"



Actor::Actor()
{
	mMotion = 0;
	mDir = Direction::Down;
	mMoveSpeed = 1;
	mLightRange = 72;
}


Actor::~Actor()
{
}

Feature Actor::GetFeature()
{
	return mFeature;
}

void Actor::SetFeature(Feature f)
{
	if (mFeature == f)
		return;
	mFeature = f;
}

uint8_t Actor::GetMotion()
{
	return mMotion;
}

void Actor::SetMotion(uint8_t m)
{
	if (mMotion == m)
		return;
	mMotion = m;
	if (onMotionChange)
		onMotionChange();
}

Direction Actor::GetDir()
{
	return mDir;
}

void Actor::SetDir(Direction dir)
{
	if (mDir == dir)
		return;
	mDir = dir;
	if (onMotionChange)
		onMotionChange();
}

Vector2UInt Actor::GetPos()
{
	return mPos;
}

void Actor::SetPos(Vector2UInt v2i)
{
	if (mPos == v2i)
		return;
	mPos = v2i;
}
void Actor::Move(Direction dir, uint16_t speed)
{
	if (_moveState.IsScrolling())
		return;
	switch (dir)
	{
	case Direction::Up:
		_moveState.Set(Horizontal::None, Vertical::Up);
		break;
	case Direction::UpRight:
		_moveState.Set(Horizontal::Right, Vertical::Up);
		break;
	case Direction::Right:
		_moveState.Set(Horizontal::Right, Vertical::None);
		break;
	case Direction::DownRight:
		_moveState.Set(Horizontal::Right, Vertical::Down);
		break;
	case Direction::Down:
		_moveState.Set(Horizontal::None, Vertical::Down);
		break;
	case Direction::DownLeft:
		_moveState.Set(Horizontal::Left, Vertical::Down);
		break;
	case Direction::Left:
		_moveState.Set(Horizontal::Left, Vertical::None);
		break;
	case Direction::UpLeft:
		_moveState.Set(Horizontal::Left, Vertical::Up);
		break;
	default:
		_moveState.Set(Horizontal::None, Vertical::None);
		break;
	}
	SetDir(dir);
	if (onMove)
		onMove(dir, speed);
}

void Actor::Update(uint32_t delta)
{
	if (_moveState.IsScrolling())
	{
		if (!_moveState.Update(delta/1000.0f)) {
			if (mFeature.IsMan() || mFeature.IsWoman())
				SetMotion(_MT_STAND);
			else if (mFeature.IsMonster())
				SetMotion(_MT_MON_STAND);
			if (onMoved)
				onMoved();
		}
	}
	
}
