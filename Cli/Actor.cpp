#include "Actor.h"



Actor::Actor() 
	:_action{_MT_STAND,ActorGender::Man,Direction::Down}
{
	mMotion = 0;
	mDir = Direction::Down;
	mMoveSpeed = 1;
	mLightRange = 72;
	_action.Enable = true;
	_actionCache.Enable = false;
	_moveInfo.Reset();
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

Vector2Float Actor::GetWPos()
{
	return mPos;
}

Action Actor::GetAction()
{
	return _action;
}

void Actor::SetWPos(Vector2Float world)
{
	if (mPos == world)
		return;
	mPos = world;
}
bool Actor::Move(Direction dir, float cellPerMs)
{
	auto xy = DecomposeDir(dir);
	_moveInfo.Set(std::get<0>(xy), std::get<1>(xy), cellPerMs);
	SetDir(dir);
	return true;
}

void Actor::Update(uint32_t delta)
{
	if (!_action.IsDone()) 
	{
		if (_moveInfo.IsMoving()) {
			_moveInfo.Update(delta);
			SetWPos(Vector2Float{ mPos.x + _moveInfo.XDelta, mPos.y + _moveInfo.YDelta });
		}

		_action.Update(delta);
		if (_action.IsDone()) 
		{
			if (_moveInfo.IsMoving())
			{
				_moveInfo.Reset();
				AlignWorld2Cell(mPos);
			}
			if (onActionCompleted)
				onActionCompleted(&_action);
		}
		_actionCache.Enable = false;// remove
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
