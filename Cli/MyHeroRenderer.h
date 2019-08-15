#pragma once
#include "HeroRenderer.h"

class MyHeroRenderer :
	public HeroRenderer
{
public:
	MyHeroRenderer();
	~MyHeroRenderer();

	virtual void SetActor(Actor *actor);

protected:
	virtual void CaclScreenPos(int32_t &x, int32_t &y);
};

