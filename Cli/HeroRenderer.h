#pragma once
#include "ActorRenderer.h"

class HeroRenderer :
	public ActorRenderer
{
public:
	HeroRenderer();
	~HeroRenderer();

protected:
	virtual void DrawImpl(uint32_t delta, Vector2Float pos, Sprite *actorSprite);
	void PlayActionSound();
};
