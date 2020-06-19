#include "Actor.h"



Actor::Actor()
{
	mMotion = 0;
	mDir = Direction::Down;
	mMoveSpeed = 1;
	mLightRange = 72;
	_action.Enable = true;
	_actionCache.Enable = false;
	_moveState.Reset();
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

Vector2Float Actor::GetPos()
{
	return mPos;
}

Action Actor::GetAction()
{
	return _action;
}

void Actor::SetPos(Vector2Float v2i)
{
	if (mPos == v2i)
		return;
	mPos = v2i;
}
bool Actor::Move(Direction dir, uint16_t speed)
{
	uint32_t ms = GetAction().Duration;
	_moveState.scrollSpeed = speed / (ms/1000.0f);
	uint8_t cnt = speed;
	switch (dir)
	{
	case Direction::Up:
		_moveState.Set(Horizontal::None, Vertical::Up, cnt);
		break;
	case Direction::UpRight:
		_moveState.Set(Horizontal::Right, Vertical::Up, cnt);
		break;
	case Direction::Right:
		_moveState.Set(Horizontal::Right, Vertical::None, cnt);
		break;
	case Direction::DownRight:
		_moveState.Set(Horizontal::Right, Vertical::Down, cnt);
		break;
	case Direction::Down:
		_moveState.Set(Horizontal::None, Vertical::Down, cnt);
		break;
	case Direction::DownLeft:
		_moveState.Set(Horizontal::Left, Vertical::Down, cnt);
		break;
	case Direction::Left:
		_moveState.Set(Horizontal::Left, Vertical::None, cnt);
		break;
	case Direction::UpLeft:
		_moveState.Set(Horizontal::Left, Vertical::Up, cnt);
		break;
	default:
		_moveState.Set(Horizontal::None, Vertical::None, cnt);
		break;
	}
	SetDir(dir);
	return true;
}

void Actor::Update(uint32_t delta)
{
	if (!_action.IsDone()) 
	{
		if (_moveState.IsScrolling()) {
			/*if(!_moveState.Update(delta))
				SetPos(Vector2Float{ mPos.x - _moveState.xDir*_moveState.count, mPos.y - _moveState.yDir*_moveState.count });
			else*/
			SetPos(Vector2Float{ mPos.x - _moveState.xScrolled, mPos.y - _moveState.yScrolled });
		}

		_action.Update(delta);
		if (_action.IsDone()) 
		{
			if (_moveState.IsScrolling())
				CompleteMove();
			if (onActionCompleted)
				onActionCompleted(&_action);
		}
		_actionCache.Enable = false;
	}
	else {
		if (_actionCache.Enable) {
			HandleAction(_actionCache);
			_actionCache.Enable = false;
		}
		else if(_action.Motion != 0)
			_actionCache=Action(0,mFeature.Gender,mDir);
	}
}

void Actor::HandleAction(Action &act)
{
	if (_action.IsDone())
	{
		if (HandleActionImpl(act)) {
			_action = act;
			if (onActionStart)
				onActionStart(&_action);
		}
	}
	else {
		_actionCache = act;
	}
}
