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
